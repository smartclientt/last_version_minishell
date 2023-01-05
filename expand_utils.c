/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:26:38 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 12:29:01 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i + 1])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_kw_dq(t_env *menv, char *str, int *i)
{
	t_string	*dst;
	char		*value;

	value = NULL;
	g_glob.g_expand_dq = 0;
	dst = new_string("");
	(*i)++;
	while (str[(*i)] && (ft_isalnum(str[(*i)]) || str[*i] == '_'))
	{
		dst = str_apend(dst, str[(*i)]);
		(*i)++;
	}
	if (find_value_with_key(menv, dst->content) != NULL)
	{
		value = find_value_with_key(menv, dst->content);
		return (free_string(&dst), value);
	}
	else
	{
		g_glob.g_expand_dq = 1;
		return (free_string(&dst), ft_substr(str, *i, ft_strlen(str)));
	}
	return (free_string(&dst), NULL);
}

char	*get_kw(t_env *menv, char *str, int *i)
{
	t_string	*dst;
	char		*value;

	value = NULL;
	dst = new_string("");
	(*i)++;
	while (str[(*i)] && str[(*i)] != ' ' && str[(*i)] != '\'')
	{
		dst = str_apend(dst, str[(*i)]);
		(*i)++;
	}
	if (find_value_with_key(menv, dst->content) != NULL)
	{
		value = find_value_with_key(menv, dst->content);
		return (free_string(&dst), value);
	}
	return (NULL);
}

char	*to_find(t_string *dst, int *i)
{
	return (ft_strchr("\0\r\t\f\v ", ((t_string *)dst)->content[*i + 1]));
}
