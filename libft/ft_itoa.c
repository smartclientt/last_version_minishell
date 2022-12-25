/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 22:07:28 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 22:11:37 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int	case_nbr(int n)
{
	int	l;

	l = nbr_len(n) - 1;
	if (n == 0)
		l = 0;
	return (l);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		l;

	l = case_nbr(n);
	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (l + 2));
	if (!str)
		return (0);
	if (n < 0)
	{
		n *= -1;
		str[i++] = '-';
	}
	str[l + 1] = '\0';
	while (l >= i)
	{
		str[l--] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}
