/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:50:40 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 11:38:03 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lst_del_first(t_list *tokens)
{
	t_list	*tmp;
	t_list	*del;

	tmp = tokens;
	if (((t_token *)tmp->content)->type == TOK_START)
	{
		del = tmp;
		tmp = tmp->next;
		free(((t_token *)del->content)->value);
		free(((t_token *)del->content));
		free((t_token *)del);
	}
	return (tmp);
}

int	main(int ac, char **av, char **env)
{
	t_env	*menv;

	if (ac > 1 && av[0])
	{
		write(2, "minishell: too many arguments\n", 30);
		return (1);
	}
	fill_env(&menv, env);
	minishell_loop(&menv);
	free_env(menv);
	return (0);
}
