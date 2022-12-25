/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 05:30:56 by shbi              #+#    #+#             */
/*   Updated: 2022/11/20 14:53:08 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *op)
{
	int	i;

	if (op[0] != '-' || op[1] != 'n')
		return (0);
	i = 2;
	while (op[i])
	{
		if (op[i] != 'n')
			return (0);
		i++;
	}
	return (1);
	return (op[0] == '-' && op[1] == 'n');
}

void	b_echo(char **arg, int fd)
{
	int	i;
	int	help;

	if (!arg || !*arg || fd == -1)
		ft_putchar_fd('\n', fd);
	else
	{
		i = 0;
		help = 0;
		while (arg[i] && is_option(arg[i]))
			i++;
		while (arg[i])
		{
			ft_putstr_fd(arg[i], fd);
			i++;
			if (arg[i])
				ft_putchar_fd(' ', fd);
		}
		if (is_option(arg[0]) == 0)
			ft_putchar_fd('\n', fd);
	}
}

