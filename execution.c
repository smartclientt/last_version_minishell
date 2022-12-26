/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 09:02:47 by shbi              #+#    #+#             */
/*   Updated: 2022/12/26 11:16:37 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Check the input if valide and give theme to the execution
the input is the list of commands
	->	we check the access of every command
	->	we change the value of the arg[0] in our list
	->	we give the command (path command) to the execution (pipes function)
*/

char	*update_cmd_path(t_env *menv, char **cmds)
{
	char	*new_path;

	new_path =  check_cmd_access(menv, cmds[0]);
	return (new_path);
}

void	execution(t_env **menv, t_list *cmds, int cmd_nbr)
{
	int	i;
	t_list *tmp;

	i = 0;
	tmp = cmds;
	while (i < cmd_nbr)
	{
		if (!is_builted(((t_cmd *)tmp->content)->args))
			((t_cmd *)tmp->content)->args[0] = update_cmd_path(*menv, ((t_cmd *)tmp->content)->args);
		tmp = tmp->next;
		i++;
	}
	if (cmd_nbr == 1 && is_builted(((t_cmd *)cmds->content)->args))
		exec_builted(menv, ((t_cmd *)cmds->content)->args);
	else
		multi_pipes(menv, cmds, cmd_nbr);
}
