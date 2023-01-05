/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:58:42 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 12:06:28 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_dollar_status(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

t_string	*add_expand(t_string *dst)
{
	t_string	*str;
	char		*word;
	int			i;
	char		*tmp;

	i = 0;
	str = new_string("");
	word = dst->content;
	while (word[i] != '\0')
	{
		if (word[i] == '$' && word[i + 1] == '?')
		{
			tmp = ft_itoa(g_glob.exit_status % 255);
			str = str_concate(str, tmp);
			free(tmp);
			i++;
		}
		else
			str = str_apend(str, word[i]);
		i++;
	}
	return (free_string(&dst), str);
}

t_string	*check_expand_status(t_string *dst)
{
	return (add_expand(dst));
}

// t_list *expand_exit_status(t_list *tokens)
// {
//     t_list  *tmp;

//     tmp = tokens;
//     while (tmp && ((t_token *)tmp->content)->type != TOK_EOL)
//     {
//         check_expand(tmp);
//         tmp = tmp->next;
//     }
//     return (tokens);
// }