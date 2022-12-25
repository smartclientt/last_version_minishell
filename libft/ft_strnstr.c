/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:47:37 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 15:48:40 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *big, const char *littel, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	j = 0;
	while (littel[i])
		i++;
	if (i == 0)
		return ((char *)big);
	while (big[j] && j < len)
	{
		l = 0;
		while (l < i && j + l < len)
		{
			if (big[j + l] != littel[l])
				break ;
			l++;
		}
		if (l == i)
			return ((char *)(big + j));
		j++;
	}
	return (0);
}
