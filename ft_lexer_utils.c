/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:31:59 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 12:34:56 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	*get_word_dq(t_env *menv, char *str, int *i)
{
	t_string	*dst;

	dst = new_string("");
	(*i)++;
	while (str[*i] != '"')
	{
		dst = str_apend(dst, str[*i]);
		(*i)++;
	}
	if (find_dollar_status(dst->content))
		dst = check_expand_status(dst);
	else if (find_dollar(((t_string *)dst)->content) == 1)
		dst = expand_path_dq(menv, dst, 0);
	(*i)++;
	return (dst);
}

t_string	*get_word_sq(t_env *menv, char *str, int *i)
{
	t_string	*dst;

	(void)menv;
	dst = new_string("");
	(*i)++;
	while (str[*i] != '\'')
	{
		dst = str_apend(dst, str[*i]);
		(*i)++;
	}
	(*i)++;
	return (dst);
}

t_string	*get_word(t_env *menv, char *str, int *i)
{
	t_string	*dst;

	dst = new_string("");
	while (!ft_strchr("\r\t\f\v>< \"' ", str[*i]) && str[*i] != '|'
		&& str[*i] != '\0' && ((*i) < (int)ft_strlen(str)))
	{
		dst = str_apend(dst, str[*i]);
		(*i)++;
	}
	while (find_dollar(((t_string *)dst)->content) == 1)
	{
		if (find_dollar_status(dst->content))
			dst = check_expand_status(dst);
		else if (find_dollar(((t_string *)dst)->content) == 1)
			dst = expand_path_dq(menv, dst, 0);
	}
	if (!dst->content)
		return (free_string(&dst), NULL);
	return (dst);
}

char	*again(t_env *menv, char *str, int *i)
{
	char		*ret;
	t_string	*dst;
	char		*tmp;

	tmp = ft_strdup("");
	ret = NULL;
	dst = NULL;
	while (!ft_strchr("\r\t\f\v>< \0", str[*i]) && str[*i] != '|'
		&& (*i) < ((int)ft_strlen(str)) && str[*i] != ' ')
	{
		if (str[*i] == '"')
			dst = get_word_dq(menv, str, i);
		else if (str[*i] == '\'')
			dst = get_word_sq(menv, str, i);
		else
			dst = get_word(menv, str, i);
		if (dst && dst->content)
			ret = ft_strjoin(tmp, ((t_string *)dst)->content);
		free_string(&dst);
		free(tmp);
		tmp = ret;
	}
	return (free_string(&dst), ret);
}

char	*new_word_v2(t_env *menv, char *str, int *i)
{
	char		*mm;

	mm = NULL;
	if (!ft_strchr("\r\t\f\v\0|>< ", str[*i]) && (*i) < ((int)ft_strlen(str)))
		mm = again(menv, str, i);
	return (mm);
}
