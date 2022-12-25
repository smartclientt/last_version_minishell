/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:53:19 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 15:54:28 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ps;
	int		ls;

	ps = (char *)s;
	ls = ft_strlen(ps);
	while (ls >= 0)
	{
		if (*(ps + ls) == (char)c)
			return (ps + ls);
		ls--;
	}
	if (*ps == (char)c)
		return ((char *)ps);
	return (0);
}
