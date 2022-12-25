/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:13:46 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 15:15:58 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dest;
	if (d == NULL && s == NULL)
		return (NULL);
	if (s <= d)
	{
		while (n--)
			*(d + n) = *(s + n);
	}
	else
		ft_memcpy(d, s, n);
	return (dest);
}
