/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:00:13 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 21:32:37 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_herdoc(int sig)
{
	(void)sig;
	g_glob.heredoc_exit = 0;
	exit(130);
}

t_string	*check_heredoc_exp(t_string *input, t_env *menv)
{
	if (find_dollar_status(((t_string *)input)->content))
			input = check_expand_status(input);
	if (find_dollar(((t_string *)input)->content) == 1)
		input = expand_path_dq(menv, input, 0);
	return (input);
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
	input = check_heredoc_exp(input, menv);
	result = ((t_string *)input)->content;
	return (g_glob.expand_heredoc = 0, free(input), result);
}
