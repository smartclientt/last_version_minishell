/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:16:50 by shbi              #+#    #+#             */
/*   Updated: 2023/01/01 02:04:02 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd(t_env **menv, char **cmd)
{
	int	status;

	status = 0;
	if (is_builted(cmd))
		return (exec_builted(menv, cmd));
	else
		return (exec_no_builted(menv, cmd));
	return (status);
}

void	pipe_logic(t_env **menv, t_list *tmp, t_tools *tools, int i)
{
	if (tools->id[i] == 0)
	{
		if (1 != tools->cmd_nbr)
		{
			if (i + 1 == tools->cmd_nbr)
				last_cmd(tools->fd, tools->prev_in, tools->prev_out);
			else if (i == 0)
				first_cmd(tools->fd, tools->prev_in, tools->prev_out);
			else
				between_cmd(tools->fd, tools->prev_in, tools->prev_out);
		}
		exit(execute_red(tmp, ((t_cmd *)tmp->content)->redirs, menv));
	}
}

void	init_tools_variables(t_tools *tools, int cmd_nbr)
{
	tools->cmd_nbr = cmd_nbr;
	tools->prev_in = -1;
	tools->prev_out = -1;
	tools->fd[0] = -1;
	tools->fd[1] = -1;
}

void	wait_exit_status(t_tools *tools)
{
	int	i;

	i = 0;
	while (waitpid(tools->id[i++], &v_glob.exit_status, 0) != -1)
		;
	if (WIFEXITED(v_glob.exit_status))
		WEXITSTATUS(v_glob.exit_status);
}

void	multi_pipes(t_env **menv, t_list *cmds, int cmd_nbr)
{
	t_tools	tools;
	t_list	*tmp;
	int		i;

	tmp = cmds;
	i = -1;
	init_tools_variables(&tools, cmd_nbr);
	while (++i < tools.cmd_nbr)
	{
		tools.prev_in = tools.fd[0];
		tools.prev_out = tools.fd[1];
		if (i + 1 != tools.cmd_nbr)
			pipe(tools.fd);
		tools.id[i] = fork();
		pipe_logic(menv, tmp, &tools, i);
		close(tools.prev_in);
		close(tools.prev_out);
		tmp = tmp->next;
	}
	wait_exit_status(&tools);
}
