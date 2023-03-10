/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf_tools2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 04:14:43 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 19:55:41 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_d(int fd, int nbr)
{
	int	count;

	count = 0;
	return (ft_putnbr_base_d(fd, nbr, "0123456789", &count));
}

int	ft_printf_i(int fd, int nbr)
{
	int	count;

	count = 0;
	return (ft_putnbr_base_d(fd, nbr, "0123456789", &count));
}

int	ft_printf_x(int fd, int nbr)
{
	int	count;

	count = 0;
	return (ft_putnbr_base_d(fd, (unsigned int)nbr,
			"0123456789abcdef", &count));
}

int	ft_printf_xx(int fd, int nbr)
{
	int	count;

	count = 0;
	return (ft_putnbr_base_d(fd, (unsigned int)nbr,
			"0123456789ABCDEF", &count));
}

int	ft_printf_u(int fd, unsigned int nbr)
{
	int	count;

	count = 0;
	return (ft_putnbr_base_d(fd, nbr, "0123456789", &count));
}
