/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:29:55 by shbi              #+#    #+#             */
/*   Updated: 2022/12/31 22:26:03 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builted(char **args)
{
	if (!ft_strncmp(args[0], "cd", 3) || !ft_strncmp(args[0], "echo", 5)
		|| !ft_strncmp(args[0], "export", 7) || !ft_strncmp(args[0], "unset", 6)
		|| !ft_strncmp(args[0], "env", 4) || !ft_strncmp(args[0], "pwd", 4)
		|| !ft_strncmp(args[0], "exit", 5))
		return (1);
	return (0);
}

int	exec_builted(t_env **menv, char **args)
{
	if (ft_strcmp(args[0], "cd"))
		return (b_cd(menv, args[1]));
	else if (ft_strcmp(args[0], "echo"))
		return (b_echo(args + 1, 1));
	else if (ft_strcmp(args[0], "export"))
		return (b_export(menv, args + 1));
	else if (ft_strcmp(args[0], "unset"))
		return (b_unset(menv, args + 1));
	else if (ft_strcmp(args[0], "env"))
		return (b_env(*menv, args + 1));
	else if (ft_strcmp(args[0], "pwd"))
		return (b_pwd(*menv));
	else if (ft_strcmp(args[0], "exit"))
		b_exit(args + 1, *menv);
	return (1);
}
