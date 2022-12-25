#include "minishell.h"

t_vector *new_vector(const char *str)
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
	{
		new->content = (char **)malloc(2 * sizeof(char *));
		new->size = 0;
		new->content[new->size] = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
		while(i < ft_strlen(str))
		{
			new->content[new->size][i] = str[i];
			i++;
		}
		new->content[new->size][i] = 0;
		new->size += 1;
		new->content[new->size] = NULL;
	}
	return (new);
}
void	print_vec(t_vector *vec)
{
	size_t i;

	i = 0;
	while (vec->content[i] != NULL)
	{
		printf("%zu\t%s\n", i, vec->content[i]);
		i++;
	}
}

t_vector *vec_append(t_vector *vec, const char *str)
{
	char **tmp_content;
	size_t	tmp_size;
	size_t	i;

	tmp_size = vec->size + 1;
	i = 0;
	tmp_content = (char **)malloc((tmp_size + 1) * sizeof(char *));
	if (tmp_content == NULL)
	{
		free_vec(&vec);
		vec = new_vector(NULL);
		return (vec);
	}
	while (i < vec->size)
	{
		tmp_content[i] = (char *)malloc((ft_strlen(vec->content[i]) + 1) * sizeof(char));
		ft_memmove(tmp_content[i] ,vec->content[i] ,ft_strlen((vec->content[i])) + 1);
		i++;
	}
	tmp_content[i] = (char *)malloc((ft_strlen(str) + 2) * sizeof(char));
	int j = 0;
	while((size_t)j <= ft_strlen(str))
	{	tmp_content[i][j] = str[j];
		j++;}
	tmp_content[tmp_size] = NULL;
	free_vec(&vec);
	vec = new_vector(NULL);
	vec->content = tmp_content;
	vec->size = tmp_size;
	return (vec);
}

void free_vec(t_vector **vec)
{
	if(vec)
	{
		if(*vec && (*vec)->content)
		{
			size_t i = 0;
			while (i < (*vec)->size)
				free((*vec)->content[i++]);
			free((*vec)->content);
		}
		if(*vec)
			free(*vec);
		*vec = NULL;
	}
}


// #include <stdio.h>

// int main()
// {
//     t_vector *str;
// 	const char *s = "youness";
	
// 	str = new_vector(s);
// 	print_vec(str);
//     str = vec_append(str, "ls");
//     print_vec(str);
//     free_vec(&str);
//     print_vec(str);
//     while (1);
//     return (0);
// }