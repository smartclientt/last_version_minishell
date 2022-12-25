/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:49:18 by shbi              #+#    #+#             */
/*   Updated: 2022/12/24 13:02:39 by shbi             ###   ########.fr       */
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

char	**sorted_array(char **array)
{
	int		i;
	char	*swap;
	int		index;

	i = 0;
	while (array[i])
	{
		index = get_index_min(array, i);
		swap = array[i];
		array[i] = array[index];
		array[index] = swap;
		i++;
	}
	return (array);
}

t_env	*print_sorted_env(t_env *menv)
{
	char	**sorted;
	int		i;

	sorted = sorted_array(key_env_to_array(menv));
	i = 0;
	while (sorted[i])
	{
		printf("declare -x ");
		printf("%s=\"%s\"\n", sorted[i],
			find_value_with_key(menv, sorted[i]));
		i++;
	}
	return (menv);
}

void	new_env_value(t_env **menv, char *key, char *new_value)
{
	t_env	*update;

	update = find_key_node(*menv, key);
	free(update->value);
	update->value = new_value;
}

int		check_export_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (0);
	else
	{
		while (arg[i] && arg[i] != '=' && (ft_isalpha(arg[i])
				|| ft_isdigit(arg[i]) || arg[i] == '_'))
			i++;
		if (!arg[i])
			return (1);
		else if (arg[i] == '=')
			return (2);
	}
	return (0);
}

void	b_export(t_env **menv, char **args)
{
	int	i;

	if (!args || !*args)
		print_sorted_env(*menv);
	else
	{
		i = 0;
		while (args[i])
		{
			if (args[i][0] == '\0')
				ft_putstr_fd("export: not valid in this context:\n", 2);
			else if (check_export_args(args[i]) == 0)
				;
			else if (check_export_args(args[i]) == 1
				&& !find_key_node(*menv, get_key(args[i])))
				env_add_end(menv, env_node(ft_strdup(args[i]),
						ft_strdup("")));
			else if (check_export_args(args[i]) == 1
				&& find_key_node(*menv, get_key(args[i])))
				new_env_value(menv, get_key(args[i]), ft_strdup(""));
			else if (check_export_args(args[i]) == 2
				&& !find_key_node(*menv, get_key(args[i])))
				env_add_end(menv, env_node(get_key(args[i]),
						get_value(args[i])));
			else if (check_export_args(args[i]) == 2
				&& find_key_node(*menv, get_key(args[i])))
				new_env_value(menv, get_key(args[i]), get_value(args[i]));
			i++;
		}
	}
}
