/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 03:39:11 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 23:05:32 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	char	*ps1;
	char	*ps2;

	ps1 = s1;
	ps2 = s2;
	if (!ps1 && !ps2)
		return (0);
	if ((*ps1 && !*ps2) || (*ps2 && !*ps1))
		return (0);
	while (*ps1 && *ps2)
	{
		if (*ps1 != *ps2)
			return (0);
		ps1++;
		ps2++;
	}
	return (1);
}

char	*ft_free(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (*s);
}

int	check_quotes(char *str)
{
	int	dq;
	int	sq;
	int	i;

	i = 0;
	sq = 0;
	dq = 0;
	g_glob.check_quotes = 0;
	while (str[i] && ((size_t)i < ft_strlen(str)))
	{
		ft_check_quotes_utils(str, &i, &sq, &dq);
		i++;
	}
	if ((sq % 2) == 1 || (dq % 2) == 1)
	{
		write(2, "Error, unclosed quotes!\n", 25);
		return (1);
	}
	return (0);
}

t_cmd	*new_cmd(char **args, t_list *redirs)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->redirs = redirs;
	return (cmd);
}

t_redir	*new_red(char *path, enum e_token type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->filepath = ft_strdup(path);
	redir->type = type;
	return (redir);
}
