/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:01:45 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 12:09:08 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_red_input(t_list *cmds, t_list *red, t_env **menv)
{
	int	fd;
	int	backup;

	fd = open(((t_redir *)red->content)->filepath, O_RDONLY, 0755);
	if (fd < 0)
	{
		ft_printf(2, "minishell : %s: ", ((t_redir *)red->content)->filepath);
		perror("");
		return ;
	}
	backup = dup(0);
	dup2(fd, 0);
	execute_red(cmds, red->next, menv);
	dup2(backup, 0);
	close(fd);
}

void	double_red_input(t_list *cmds, t_list *red, t_env **menv)
{
	int	fd[2];
	int	backup;

	pipe(fd);
	backup = dup(0);
	ft_putstr_fd(((t_redir *)red->content)->filepath, fd[1]);
	close(fd[1]);
	dup2(fd[0], 0);
	execute_red(cmds, red->next, menv);
	dup2(backup, 0);
	close(fd[0]);
}

void	one_red_output(t_list *cmds, t_list *red, t_env **menv)
{
	int	fd;
	int	backup;

	fd = open(((t_redir *)red->content)->filepath,
			O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd < 0)
	{
		ft_printf(2, "minishel: %s: Permission denied\n",
			((t_redir *)red->content)->filepath);
		return ;
	}
	backup = dup(1);
	dup2(fd, 1);
	execute_red(cmds, red->next, menv);
	dup2(backup, 1);
	close(fd);
}

void	double_red_output(t_list *cmds, t_list *red, t_env **menv)
{
	int	fd;
	int	backup;

	fd = open(((t_redir *)red->content)->filepath,
			O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (fd < 0)
	{
		ft_printf(2, "minishel: %s: Permission denied\n",
			((t_redir *)red->content)->filepath);
		return ;
	}
	backup = dup(1);
	dup2(fd, 1);
	execute_red(cmds, red->next, menv);
	dup2(backup, 1);
	close(fd);
}

int	execute_red(t_list *cmds, t_list *red, t_env **menv)
{
	if (!red && ((t_cmd *)cmds->content)->args[0])
	{
		return (g_glob.exit_status = run_cmd(menv,
				((t_cmd *)cmds->content)->args));
	}
	if (((t_redir *)red->content)->type == TOK_RINPUT)
		one_red_input(cmds, red, menv);
	else if (((t_redir *)red->content)->type == TOK_DRINPUT)
		double_red_input(cmds, red, menv);
	else if (((t_redir *)red->content)->type == TOK_ROUTPUT)
		one_red_output(cmds, red, menv);
	else if (((t_redir *)red->content)->type == TOK_DROUTPUT)
		double_red_output(cmds, red, menv);
	return (0);
}
