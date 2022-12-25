/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 22:27:09 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 22:36:57 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_str(const char *s, char c)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (s[i])
	{
		if (s[i] == c)
			while (s[i] == c && s[i])
				i++;
		else
		{
			while (s[i] != c && s[i])
				i++;
			r++;
		}
	}
	return (r);
}

int	get_len(const char *s, char c, int *index)
{
	int	r;

	r = 0;
	while (s[*index] && s[*index] != c)
	{
		(*index)++;
		r++;
	}
	return (r);
}

int	get_index(const char *s, char c, int *index)
{
	while (s[*index])
	{
		if (s[*index] != c)
			break ;
		(*index)++;
	}
	return (*index);
}

static char	**spliting(char const *s, char c, char **str, int i)
{
	int	index;
	int	point;
	int	r;
	int	j;

	index = 0;
	while (++i < count_str((char *)s, c))
	{
		point = get_index((char *)s, c, &index);
		r = get_len(s, c, &index);
		str[i] = (char *)malloc(sizeof(char) * (r + 1));
		if (!str[i])
		{
			j = 0;
			while (j < i && str[j])
				free(str[j++]);
			free(str);
			return (0);
		}
		str[i][r] = '\0';
		while (--r >= 0)
			str[i][r] = s[point + r];
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * count_str(s, c) + 1);
	if (!str)
		return (NULL);
	i = -1;
	str = spliting(s, c, str, i);
	return (str);
}
