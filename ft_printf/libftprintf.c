/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:29:41 by shbi              #+#    #+#             */
/*   Updated: 2022/12/29 22:23:08 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_conversion(int fd, va_list ap, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_printf_c(fd, va_arg(ap, int));
	if (c == 's')
		count += ft_printf_s(fd, va_arg(ap, char *));
	if (c == 'p')
		count += ft_printf_p(fd, va_arg(ap, unsigned long int *));
	if (c == 'd')
		count += ft_printf_d(fd, va_arg(ap, int));
	if (c == 'i')
		count += ft_printf_i(fd, va_arg(ap, int));
	if (c == 'x')
		count += ft_printf_x(fd, va_arg(ap, int));
	if (c == 'X')
		count += ft_printf_xx(fd, va_arg(ap, int));
	if (c == 'u')
		count += ft_printf_u(fd, va_arg(ap, int));
	if (c == '%')
		count += write (fd, "%%", 1);
	return (count);
}

int	ft_printf(int fd,const char *format, ...)
{
	int		i;
	int		count;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += ft_conversion(fd, ap, format[++i]);
		else if (format[i] != '%')
			count += write(fd, &format[i], 1);
		else
			count += write(fd, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
