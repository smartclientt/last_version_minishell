/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:38:59 by shbi              #+#    #+#             */
/*   Updated: 2023/01/02 02:59:35 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_of_args(char **args)
{
	int	l;

	l = -1;
	while (args[++l])
		;
	return (l);
}

int	is_nbr(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i])
		return (0);
	return (1);
}

void	b_exit(char **args, t_env *menv)
{
	int	exit_status;

	exit_status = 0;
	if (args)
	{
		if (nbr_of_args(args) == 0)
			ft_printf(2, "exit\n");
		else if (!is_nbr(args[0]))
		{
			ft_printf(2, "exit\nminishell: exit: %s: numeric argument required\n",
				args[0]);
			exit_status = 255;
		}
		else if (is_nbr(args[0]) && nbr_of_args(args) == 1)
			exit_status = ft_atoi(args[0]) % 256;
		else if (is_nbr(args[0]) && nbr_of_args(args) > 1)
		{
			ft_printf(2, "exit\nminishell: exit: too many arguments\n");
			v_glob.exit_status = 1;
			return ;
		}
	}
	v_glob.exit_status = exit_status;
	//neeed to free env and cmds and readline;
	free_env(menv);
	exit(exit_status);
}
