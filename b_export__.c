/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export__.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:04:54 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 21:04:05 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_array_2d(sorted);
	return (menv);
}

void	new_env_value(t_env **menv, char *key, char *new_value)
{
	t_env	*update;

	update = find_key_node(*menv, key);
	free(update->value);
	update->value = new_value;
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
