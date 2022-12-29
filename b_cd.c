/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 04:21:36 by shbi              #+#    #+#             */
/*   Updated: 2022/12/29 04:13:45 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pwd_to_env(t_env **menv)
{
	char	pwd[PATH_MAX];

	env_add_end(menv, env_node(ft_strdup("PWD"),
			ft_strdup(getcwd(pwd, sizeof(pwd)))));
}

void	add_oldpwd_to_env(t_env **menv, t_env *pwd)
{
	env_add_end(menv, env_node(ft_strdup("OLDPWD"), ft_strdup(pwd->value)));
}

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
		pwd->value = ft_strdup(getcwd(pwd_str, sizeof(pwd_str)));
	}
}

int		cd_home(t_env **menv)
{
	char	*home;

	home = find_value_with_key(*menv, "HOME");
	if (!home)
		error_msg("cd: HOME not set\n");
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
		error_msg("cd: OLDPWD not set\n");
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
	if (!path || ft_strcmp("~", path))
		return (cd_home(menv));
	else
	{
		if (ft_strcmp("-", path))
			return (cd_oldpwd(menv));
		else
		{
			if (chdir(path) == -1)
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
