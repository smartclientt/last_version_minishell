/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 04:21:36 by shbi              #+#    #+#             */
/*   Updated: 2023/01/02 03:41:52 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_pwd_and_oldpwd(t_env **menv)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	pwd_str[PATH_MAX];

	pwd = find_key_node(*menv, ft_strdup("PWD"));
	if (!pwd)
		add_pwd_to_env(menv);
	else
	{
		oldpwd = find_key_node(*menv, ft_strdup("OLDPWD"));
		if (!oldpwd)
			add_oldpwd_to_env(menv, pwd);
		else
		{
			free(oldpwd->value);
			oldpwd->value = pwd->value;
		}
		pwd->value = ft_strdup(getcwd(pwd_str, PATH_MAX));
	}
}

int	cd_home(t_env **menv)
{
	char	*home;

	home = find_value_with_key(*menv, "HOME");
	if (!home)
		ft_printf(2, "minishell: cd: HOME not set\n");
	else if (chdir(home) == -1)
		perror("minishell: cd: ");
	else
	{
		new_pwd_and_oldpwd(menv);
		return (0);
	}
	return (1);
}

int	cd_oldpwd(t_env **menv)
{
	char	*oldpwd;

	oldpwd = find_value_with_key(*menv, "OLDPWD");
	if (!oldpwd)
		ft_printf(2, "minishell: cd: OLDPWD not set\n");
	else
	{
		if (chdir(oldpwd) == -1)
			perror("minishell: cd: ");
		else
		{
			new_pwd_and_oldpwd(menv);
			return (0);
		}
	}
	return (1);
}

int	b_cd(t_env **menv, char *path)
{
	char	buffer[PATH_MAX];

	if (!path || ft_strcmp("~", path))
		return (cd_home(menv));
	else
	{
		if (ft_strcmp("-", path))
			return (cd_oldpwd(menv));
		else
		{
			if (getcwd(buffer, PATH_MAX) == NULL)
			{
				cd_home(menv);
				return (1);
			}
			else if (chdir(path) == -1)
			{
				perror("minishell: cd: ");
				return (1);
			}
			else
			{
				new_pwd_and_oldpwd(menv);
				return (0);
			}
		}
	}
	return (1);
}
