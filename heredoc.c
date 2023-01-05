/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:00:13 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 12:06:28 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_herdoc(int sig)
{
	(void)sig;
	g_glob.heredoc_exit = 0;
	exit(130);
}

char	*ft_heredocs(char *file, t_env *menv)
{
	t_string	*input;
	char		*buffer;
	char		*result;
	t_string	*tmp;

	input = new_string("");
	while (1)
	{
		tmp = input;
		buffer = readline("> ");
		if (!buffer || ft_strncmp(buffer, file, ft_strlen(file) + 1) == 0
			|| !g_glob.heredoc_exit)
		{
			free(buffer);
			break ;
		}
		tmp = str_concate(tmp, buffer);
		input = str_apend(tmp, '\n');
		free(buffer);
	}
	if (find_dollar(((t_string *)input)->content) == 1)
		input = expand_path_dq(menv, input, 0);
	result = ((t_string *)input)->content;
	return (free(input), result);
}
