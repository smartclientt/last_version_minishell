/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:03:20 by shbi              #+#    #+#             */
/*   Updated: 2022/12/30 17:04:35 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_key(char *s1, char *s2)
{
	char	*ps1;
	char	*ps2;

	ps1 = s1;
	ps2 = s2;
	while (*ps1 || *ps2)
	{
		if (*ps1 != *ps2)
			return (*ps1 - *ps2);
		ps1++;
		ps2++;
	}
	if (*ps1 && !*ps2)
		return (*ps1 - *ps2);
	else if (!*ps1 && *ps2)
		return (*ps2 - *ps1);
	return (0);
}

int	env_size(t_env *lst)
{
	int		c;
	t_env	*pl;

	c = 0;
	pl = lst;
	while (pl)
	{
		pl = pl->next;
		c++;
	}
	return (c);
}

char	**key_env_to_array(t_env *menv)
{
	char	**str_env;
	int		i;

	str_env = malloc(sizeof(char *) * (env_size(menv) + 1));
	if (!str_env)
		return (NULL);
	i = 0;
	while (menv)
	{
		str_env[i] = ft_strdup(menv->key);
		if (!str_env[i])
			ft_free(str_env);
		i++;
		menv = menv->next;
	}
	str_env[i] = NULL;
	return (str_env);
}

char	**env_to_array(t_env *menv)
{
	char	**str_env;
	char	*temp;
	int		i;

	str_env = malloc(sizeof(char *) * (env_size(menv) + 1));
	if (!str_env)
		return (NULL);
	i = 0;
	while (menv)
	{
		temp = ft_strjoin(menv->key, "=");
		str_env[i] = ft_strjoin(temp, menv->value);
		free(temp);
		if (!str_env[i])
			ft_free(str_env);
		i++;
		menv = menv->next;
	}
	str_env[i] = NULL;
	return (str_env);
}

int	get_index_min(char **array, int i)
{
	int		index;
	char	*min;

	index = i;
	min = array[i];
	while (array[i + 1])
	{
		if (cmp_key(min, array[i + 1]) > 0)
		{
			min = array[i + 1];
			index = i + 1;
		}
		i++;
	}
	return (index);
}
