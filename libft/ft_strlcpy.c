/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:33:54 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 15:37:20 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*d;
	const char	*s;
	size_t		ls;

	d = dst;
	s = src;
	ls = ft_strlen(s);
	if (dstsize == 0)
		return (ls);
	while (dstsize - 1 > 0 && *s)
	{
		*d++ = *s++;
		dstsize--;
	}
	*d = '\0';
	return (ls);
}
