/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:21:22 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 12:23:51 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(t_env	*menv)
{
	t_env	*pwd_node;
	char	pwd[PATH_MAX];

	pwd_node = find_key_node(menv, ft_strdup("PWD"));
	if (!pwd_node)
		printf("%s\n", getcwd(pwd, PATH_MAX));
	else
		printf("%s\n", pwd_node->value);
	return (0);
}
