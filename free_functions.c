/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 22:11:40 by shbi              #+#    #+#             */
/*   Updated: 2023/01/02 02:59:26 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *menv)
{
	t_env	*next;

	next = menv;
	while (menv)
	{
		next = menv->next;
		free(menv->key);
		free(menv->value);
		free(menv);
		menv = next;
	}
}

void	free_array_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_redir(t_list *redir)
{
	t_list	*next;

	next = redir;
	while (redir)
	{
		next = redir->next;
		free(((t_redir *)redir)->filepath);
		redir = next;
	}
}

void	free_cmds(t_list *cmds)
{
	t_list	*next;

	next = cmds;
	while (cmds)
	{
		next = cmds->next;
		free_array_2d(((t_cmd *)cmds)->args);
		free_redir(((t_cmd *)cmds)->redirs);
		free(((t_cmd *)cmds));
		cmds = next;
	}
}
