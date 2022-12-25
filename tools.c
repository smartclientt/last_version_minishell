/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 03:39:11 by shbi              #+#    #+#             */
/*   Updated: 2022/12/24 20:30:09 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	char	*ps1;
	char	*ps2;

	ps1 = s1;
	ps2 = s2;

	if ((*ps1 && !*ps2) || (*ps2 && !*ps1))
		return (0);
	while (*ps1 && *ps2)
	{
		if (*ps1 != *ps2)
			return (0);
		ps1++;
		ps2++;
	}
	return (1);
}

char	*ft_free(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (*s);
}
