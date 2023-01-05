/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:26:26 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 19:56:17 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include<unistd.h>
# include<stdarg.h>
# include<stdio.h>
# include "../libft/libft.h"

int	ft_printf(int fd, const char *format, ...);
int	ft_printf_c(int fd, int c);
int	ft_putchar(int fd, int c);
int	ft_printf_s(int fd, char *str);
int	ft_printf_p(int fd, unsigned long int *nbr);
int	ft_putnbr_base_d(int fd, long int nbr, char *base, int *count);
int	ft_putnbr_base(int fd, unsigned long int nbr, char *base, int *count);
int	ft_printf_d(int fd, int nbr);
int	ft_printf_i(int fd, int nbr);
int	ft_printf_x(int fd, int nbr);
int	ft_printf_xx(int fd, int nbr);
int	ft_putchar(int fd, int c);
int	ft_printf_u(int fd, unsigned int nbr);
int	ft_conversion(int fd, va_list ap, char c);

#endif