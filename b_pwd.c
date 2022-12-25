/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:21:22 by shbi              #+#    #+#             */
/*   Updated: 2022/11/23 18:42:21 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_pwd(t_env	*menv)
{
	t_env	*pwd_node;
	char	pwd[PATH_MAX];

	pwd_node = find_key_node(menv, ft_strdup("PWD"));
	if (!pwd_node)
		printf("%s\n", getcwd(pwd, sizeof(pwd)));
	else
		printf("%s\n", pwd_node->value);
}
