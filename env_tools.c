/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 05:45:34 by shbi              #+#    #+#             */
/*   Updated: 2022/12/23 18:52:40 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_node(char *key, char *value)
{
	t_env	*new_node = NULL;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	env_add_end(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (*lst && new)
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

char	*get_key(char *env)
{
	int		i;
	char	*key;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *env)
{
	int		i;
	int		len;
	int		start;
	char	*value;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	start = ++i;
	len = 0;
	while (env[i++])
		len++;
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (env[start])
	{
		value[i++] = env[start];
		start++;
	}
	value[i] = '\0';
	return (value);
}

void	fill_env(t_env **menv, char **env)
{
	int		i;

	i = 0;
	if (!*env || !env)
		create_if_no_env(menv);
	else
	{
		while (env[i])
		{
			env_add_end(menv, env_node(get_key(env[i]), get_value(env[i])));
			i++;
		}
	}
}
