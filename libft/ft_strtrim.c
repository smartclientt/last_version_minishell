/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:01:42 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 23:06:05 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_char(char c, char *set)
{
	if (ft_strchr(set, c))
		return (1);
	return (0);
}

size_t	count_start(char *s1, char *set)
{
	int	i;

	i = 0;
	while (check_char(s1[i], set))
		i++;
	return (i);
}

size_t	count_end(char *s1, char *set)
{
	int	i;

	i = ft_strlen(s1);
	while (check_char(s1[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tr;
	size_t	len;
	size_t	start;
	size_t	end;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	start = count_start((char *)s1, (char *)set);
	end = count_end((char *)s1, (char *)set);
	if (start == end + 1)
		return (ft_strdup(""));
	len = end - start + 1;
	tr = ft_substr(s1, start, len);
	return (tr);
}
