/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:28:46 by shbi              #+#    #+#             */
/*   Updated: 2023/01/02 03:42:21 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pwd_to_env(t_env **menv)
{
	char	pwd[PATH_MAX];

	env_add_end(menv, env_node(ft_strdup("PWD"),
			ft_strdup(getcwd(pwd, PATH_MAX))));
}

void	add_oldpwd_to_env(t_env **menv, t_env *pwd)
{
	env_add_end(menv, env_node(ft_strdup("OLDPWD"), ft_strdup(pwd->value)));
}
