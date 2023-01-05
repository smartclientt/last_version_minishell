/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:29:45 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 21:30:23 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	*expand_utils(t_string *dst, t_string *str, t_string *key)
{
	t_string	*tmp;

	if (key->content == NULL)
		return (free_string(&dst), free_string(&str), new_string(""));
	if (g_glob.g_expand_dq == 1)
	{
		tmp = str_concate(str, key->content);
		return (free_string(&dst), free_string(&key),
			g_glob.g_expand_dq = 0, tmp);
	}
	return (NULL);
}

t_string	*expand_utils_(t_string *str, t_string *key, t_string *dst)
{
	g_glob.expand_heredoc = 0;
	return (free_string(&str), free_string(&key), dst);
}

void	expand_utils__(t_string *str, t_string *key, t_string *dst, int *i)
{
	str = str_concate(str, key->content);
	if (!ft_strchr("\r\t\0\f\v|><\"", ((t_string *)dst)->content[*i]))
		str = str_apend(str, ((t_string *)dst)->content[*i]);
}

void	expand_init(t_string **key, t_string **str)
{	
	*key = new_string(NULL);
	*str = new_string("");
}

t_string	*expand_path_dq(t_env *menv, t_string *dst, int i)
{
	t_string	*key;
	t_string	*str;

	expand_init(&key, &str);
	if (g_glob.expand_heredoc == 1)
		return (expand_utils_(str, key, dst));
	while (((t_string *)dst)->content[i] != '\0'
		&& i < (int)((t_string *)dst)->size)
	{
		if (((t_string *)dst)->content[i] == '$' && to_find(dst, &i))
			return (free_string(&dst), free_string(&key), str_apend(str, '$'));
		else if (((t_string *)dst)->content[i] == '$')
		{
			key->content = get_kw_dq(menv, ((t_string *)dst)->content, &i);
			if (key->content == NULL || g_glob.g_expand_dq == 1)
				return (expand_utils(dst, str, key));
			expand_utils__(str, key, dst, &i);
		}
		else
			str = str_apend(str, ((t_string *)dst)->content[i]);
		i++;
	}
	return (free_string(&dst), free(key), str);
}
