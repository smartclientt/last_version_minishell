/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:44:39 by shbi              #+#    #+#             */
/*   Updated: 2022/12/30 17:12:19 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*remove_node(t_env *menv, char *key)
{
	t_env	*next;
	t_env	*new_env;

	new_env = NULL;
	while (menv)
	{
		next = menv->next;
		menv->next = NULL;
		if (cmp_key(menv->key, key) == 0)
		{
			free(menv->value);
			free(menv->key);
			free(menv);
		}
		else
		{
			env_add_end(&new_env, env_node(menv->key, menv->value));
			free(menv);
		}
		menv = next;
	}
	free(key);
	return (new_env);
}

int	check_unset_args(char *arg)
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

int	b_unset(t_env **menv, char **args)
{
	int		i;
	t_env	*new_env;

	new_env = *menv;
	if (!args || !*args)
		return (0);
	else
	{
		i = -1;
		while (args[++i])
		{
			if (!find_key_node(new_env, ft_strdup(args[i])))
			{
				if (check_unset_args(args[i]) == 0
					|| check_unset_args(args[i]) == 2)
					ft_printf(2,
						"minishell: export: `%s': not a valid identifier\n",
						args[i]);
			}
			else if (find_key_node(new_env, ft_strdup(args[i])))
				new_env = remove_node(new_env, ft_strdup(args[i]));
		}
	}
	*menv = new_env;
	return (0);
}
