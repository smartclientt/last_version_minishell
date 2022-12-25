/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:48:49 by shbi              #+#    #+#             */
/*   Updated: 2022/11/30 13:17:23 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_if_no_env(t_env **menv)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	env_add_end(menv, env_node("PATH","/usr/bin:/bin:/usr/sbin:/sbin"));
	env_add_end(menv, env_node("PWD", tmp));
	env_add_end(menv, env_node("SHLVL","0"));
}

void	print_env(t_env *menv)
{
	while (menv)
	{
		ft_putstr_fd(menv->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(menv->value, 1);
		ft_putstr_fd("\n", 1);
		menv = menv->next;
	}
}

char	*find_value_with_key(t_env *menv, char *key)
{
	// i need to check error if no key in the env;
	while (menv)
	{
		if (ft_strcmp(menv->key, key) == 1
			&& ft_strlen(menv->key) == ft_strlen(key))
			return (menv->value);
		menv = menv->next;
	}
	return (NULL);
}

t_env	*find_key_node(t_env *menv, char *key)
{
	// i need to check error error if no key in the env;
	while (menv)
	{
		if (ft_strcmp(menv->key, key) == 1
			&& ft_strlen(menv->key) == ft_strlen(key))
		{
			free(key);
			return (menv);
		}
		menv = menv->next;
	}
	free(key);
	return (NULL);
}
