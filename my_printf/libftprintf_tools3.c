/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf_tools3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:02:00 by shbi              #+#    #+#             */
/*   Updated: 2022/12/29 22:14:20 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_c(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_printf_s(int fd, char *str)
{
	if (!str)
		return (write(fd, "(null)", 6));
	return (write(fd, str, ft_strlen(str)));
}

int	ft_printf_p(int fd, unsigned long int *nbr)
{
	unsigned long int	adr;
	int					count;

	adr = (unsigned long int)nbr;
	count = 0;
	count += write(fd, "0x", 2);
	return (ft_putnbr_base(fd, adr, "0123456789abcdef", &count));
}
