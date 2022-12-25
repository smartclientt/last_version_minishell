/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:32:12 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 15:33:46 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ls;
	size_t	ld;
	size_t	r;

	ls = ft_strlen(src);
	ld = ft_strlen(dst);
	if (dstsize == 0)
		return (ls);
	if (ld >= dstsize)
		r = ls + dstsize;
	else
		r = ls + ld;
	while (*src && ld < dstsize - 1)
	{
		*(dst + ld) = *src;
		src++;
		ld++;
	}
	*(dst + ld) = '\0';
	return (r);
}
