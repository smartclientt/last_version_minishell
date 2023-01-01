/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf_tools1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:29:31 by shbi              #+#    #+#             */
/*   Updated: 2022/12/29 22:32:57 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_putnbr_base(int fd, unsigned long int nbr, char *base, int *count)
{
	unsigned long int	l;

	l = ft_strlen(base);
	if (nbr < 0)
	{
		*count += ft_putchar(fd, '-');
		ft_putnbr_base(fd, nbr * (-1), base, count);
	}
	else if (nbr < l)
	{
		*count += ft_putchar(fd, base[nbr]);
	}
	else
	{
		ft_putnbr_base(fd, nbr / l, base, count);
		ft_putnbr_base(fd, nbr % l, base, count);
	}
	return (*count);
}

int	ft_putnbr_base_d(int fd, long int nbr, char *base, int *count)
{
	long int	l;

	l = ft_strlen(base);
	if (nbr < 0)
	{
		*count += ft_putchar(fd, '-');
		ft_putnbr_base(fd, nbr * (-1), base, count);
	}
	else if (nbr < l)
	{
		*count += ft_putchar(fd, base[nbr]);
	}
	else
	{
		ft_putnbr_base(fd, nbr / l, base, count);
		ft_putnbr_base(fd, nbr % l, base, count);
	}
	return (*count);
}
