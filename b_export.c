/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:49:18 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 12:24:22 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (0);
	else
	{
		while (arg[i] && arg[i] != '=' && ((arg[i] != '+' && arg[i + 1] != '=')
				|| ft_isalpha(arg[i])
				|| ft_isdigit(arg[i]) || arg[i] == '_'))
			i++;
		if (!arg[i])
			return (1);
		else if (arg[i] == '+' && arg[i + 1] == '=')
		{
			if (!arg[i + 2])
				return (3);
			return (4);
		}
		else if (arg[i] == '=')
			return (2);
	}
	return (0);
}

char	*get_key_plus(char *env)
{
	int		i;
	char	*key;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '+')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '+')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	join_env_value(t_env **menv, char *key, char *new_value)
{
	t_env	*update;
	char	*join_value;

	update = find_key_node(*menv, key);
	join_value = ft_strjoin(update->value, new_value);
	free(new_value);
	free(update->value);
	update->value = join_value;
}

void	b_export_(t_env **menv, char **args, int i)
{
	if (check_export_args(args[i]) == 0)
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n",
			args[i]);
	else if (check_export_args(args[i]) == 3
		&& !find_key_node(*menv, get_key_plus(args[i])))
		env_add_end(menv, env_node(get_key_plus(args[i]), ft_strdup("")));
	else if (check_export_args(args[i]) == 3
		&& find_key_node(*menv, get_key_plus(args[i])))
		join_env_value(menv, get_key_plus(args[i]), ft_strdup(""));
	else if (check_export_args(args[i]) == 4
		&& !find_key_node(*menv, get_key_plus(args[i])))
		env_add_end(menv, env_node(get_key_plus(args[i]), get_value(args[i])));
	else if (check_export_args(args[i]) == 4
		&& find_key_node(*menv, get_key_plus(args[i])))
		join_env_value(menv, get_key_plus(args[i]), get_value(args[i]));
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
}

int	b_export(t_env **menv, char **args)
{
	int	i;

	if (!args || !*args)
		print_sorted_env(*menv);
	else
	{
		i = 0;
		while (args[i])
		{
			b_export_(menv, args, i);
			i++;
		}
	}
	return (0);
}
