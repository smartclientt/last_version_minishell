/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 22:37:07 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 22:49:56 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	d = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!d)
		return (NULL);
	i = -1;
	while (s1[++i])
		d[i] = s1[i];
	j = -1;
	while (s2[++j])
		d[i++] = s2[j];
	d[i] = '\0';
	return (d);
}
