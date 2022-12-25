/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:21:18 by shbi              #+#    #+#             */
/*   Updated: 2022/11/03 23:00:45 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ps;
	int		i;

	i = -1;
	ps = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ps)
		return (NULL);
	while (s1[++i])
		ps[i] = s1[i];
	ps[i] = '\0';
	return (ps);
}
 