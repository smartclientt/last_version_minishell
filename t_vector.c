/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:15:50 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 13:20:12 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_vectot_util(t_vector *new, const char *str, size_t *i)
{
	new->content = (char **)malloc(2 * sizeof(char *));
	new->size = 0;
	new->content[new->size] = (char *)malloc(
			(ft_strlen(str) + 1) * sizeof(char));
	while ((size_t)i < ft_strlen(str))
	{
		new->content[new->size][*i] = str[*i];
		i++;
	}
	new->content[new->size][*i] = 0;
	new->size += 1;
	new->content[new->size] = NULL;
}

t_vector	*new_vector(const char *str)
{
	t_vector	*new;
	size_t		i;

	i = 0;
	new = (t_vector *)malloc(sizeof(t_vector));
	if (new == NULL)
		return (NULL);
	if (str == NULL)
	{
		new->content = (char **)malloc(sizeof(char *));
		new->size = 0;
		new->content[new->size] = NULL;
	}
	else
		new_vectot_util(new, str, &i);
	return (new);
}

void	vec_append_utils(size_t *i, char **tmp_content, t_vector *vec)
{
	while (*i < vec->size)
	{
		tmp_content[*i] = (char *)malloc((
					ft_strlen(vec->content[*i]) + 1) * sizeof(char));
		ft_memmove(tmp_content[*i], vec->content[*i],
			ft_strlen((vec->content[*i])) + 1);
		*i++;
	}
}

t_vector	*vec_append(t_vector *vec, const char *str)
{
	char	**tmp_content;
	size_t	tmp_size;
	size_t	i;
	int		j;

	tmp_size = vec->size + 1;
	i = 0;
	j = 0;
	tmp_content = (char **)malloc((tmp_size + 1) * sizeof(char *));
	if (tmp_content == NULL)
		return (free_vec(&vec), vec = new_vector(NULL), vec);
	vec_append_utils(&i, tmp_content, vec);
	tmp_content[i] = (char *)malloc((ft_strlen(str) + 2) * sizeof(char));
	while ((size_t)j <= ft_strlen(str))
	{
		tmp_content[i][j] = str[j];
		j++;
	}
	tmp_content[tmp_size] = NULL;
	free_array_2d(vec->content);
	return (vec->content = tmp_content, vec->size = tmp_size, vec);
}

void	free_vec(t_vector **vec)
{
	size_t	i;

	i = 0;
	if (vec)
	{
		if (*vec && (*vec)->content)
		{
			while (i < (*vec)->size)
				free((*vec)->content[i++]);
			free((*vec)->content);
		}
		if (*vec)
			free(*vec);
		*vec = NULL;
	}
}
