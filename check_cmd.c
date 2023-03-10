/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:41:38 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 12:23:30 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access_path(char *path)
{
	if (!path || !*path)
		return (-3);
	else if (!cmd_is_path(path))
		return (-2);
	else
	{
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (1);
			else
				return (-1);
		}
	}
	return (0);
}

void	free_path_env(char **path_env)
{
	int	i;

	i = 0;
	while (path_env[i])
	{
		free(path_env[i]);
		i++;
	}
	free(path_env);
}

int	cmd_is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*cmd_is_not_path(t_env *menv, char *cmd)
{
	char	**path_env;
	char	*first_cmd;
	char	*path;
	int		i;

	path_env = ft_split(find_value_with_key(menv, "PATH"), ':');
	first_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (path_env[i])
	{
		path = ft_strjoin(path_env[i], first_cmd);
		if (check_access_path(path) == 1)
		{
			free(first_cmd);
			free_path_env(path_env);
			free(cmd);
			return (path);
		}
		free(path);
		i++;
	}
	free(first_cmd);
	free_path_env(path_env);
	ft_printf(2, "minishell: %s: command not found\n", cmd);
	return (cmd);
}

char	*check_cmd_access(t_env *menv, char *cmd)
{
	if (!find_key_node(menv, ft_strdup("PATH")))
		ft_printf(2, "minishell: %s: command not found\n", cmd);
	else if (!*cmd)
		ft_printf(2, "minishell: %s: permession denied\n", cmd);
	else if (is_builted(&cmd))
		;
	else if (!cmd_is_path(cmd))
		return (cmd_is_not_path(menv, cmd));
	else
	{
		if (check_access_path(cmd) == 1)
			return (cmd);
		else if (check_access_path(cmd) == -1)
			ft_printf(2, "minishell: %s: permession denied\n", cmd);
		else if (check_access_path(cmd) == 0)
			ft_printf(2, "minishell: %s: No such file or directory\n", cmd);
	}
	return (cmd);
}
