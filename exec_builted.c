/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:29:55 by shbi              #+#    #+#             */
/*   Updated: 2022/12/24 10:54:25 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builted(char **args)
{
	if (ft_strcmp(args[0], "cd") || ft_strcmp(args[0], "echo") ||
		ft_strcmp(args[0], "export") || ft_strcmp(args[0], "unset") ||
		ft_strcmp(args[0], "env") || ft_strcmp(args[0], "pwd") ||
		ft_strcmp(args[0], "exit"))
		return (1);
	return (0);
}
void	exec_builted(t_env **menv, char **args)
{
	if (ft_strcmp(args[0], "cd"))
		b_cd(menv, args[1]);
	else if (ft_strcmp(args[0], "echo"))
		b_echo(args + 1, 1);
	else if (ft_strcmp(args[0], "export"))
		b_export(menv, args + 1);
	else if (ft_strcmp(args[0], "unset"))
		b_unset(menv, args + 1);
	else if (ft_strcmp(args[0], "env"))
		b_env(*menv, args + 1);
	else if (ft_strcmp(args[0], "pwd"))
		b_pwd(*menv);
	else if (ft_strcmp(args[0], "exit"))
		;
}
