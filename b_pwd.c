/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:21:22 by shbi              #+#    #+#             */
/*   Updated: 2022/12/29 03:52:58 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_pwd(t_env	*menv)
{
	t_env	*pwd_node;
	char	pwd[PATH_MAX];

	pwd_node = find_key_node(menv, ft_strdup("PWD"));
	if (!pwd_node)
		printf("%s\n", getcwd(pwd, sizeof(pwd)));
	else
		printf("%s\n", pwd_node->value);
	return (0);
}
