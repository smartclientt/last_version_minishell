/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:22:18 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 23:25:59 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_cmd(int fd[2], int prev_in, int prev_out)
{
	(void)prev_in;
	(void)prev_out;
	close(fd[0]);
	if (dup2(fd[1], 1) == -1)
		error_msg("error dup first cmd\n");
	close(fd[1]);
}

void	between_cmd(int fd[2], int prev_in, int prev_out)
{
	close(fd[0]);
	close(prev_out);
	if (dup2(prev_in, 0) == -1)
		error_msg("2-error dup between cmd\n");
	close(prev_in);
	if (dup2(fd[1], 1) == -1)
		error_msg("1-error dup between cmd\n");
	close(fd[1]);
}

void	last_cmd(int fd[2], int prev_in, int prev_out)
{
	(void)fd;
	close(prev_out);
	if (dup2(prev_in, 0) == -1)
		error_msg("error dup last cmd\n");
	close(prev_in);
}

int	returned_exit_status(int status)
{
	if (WIFEXITED(status))
		WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (status == 2)
			return (ft_printf(2, "\n"), 130);
		if (status == 3)
			return (ft_printf(2, "Quit: 3\n"), 131);
	}
	return (status % 255);
}

int	exec_no_builted(t_env **menv, char **cmd)
{
	int	id;
	int	checker;
	int	status;

	id = fork();
	if (id == 0)
	{
		rl_catch_signals = 1;
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		checker = check_access_path(cmd[0]);
		if (checker == 1)
		{
			if (execve(cmd[0], cmd, env_to_array(*menv)) == -1)
				perror("minishell: ");
		}
		else if (checker == -1 || checker == -3)
			exit(126);
		else if (checker == 0 || checker == -2)
			exit(127);
	}
	waitpid(id, &status, 0);
	return (returned_exit_status(status));
}
