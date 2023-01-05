
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:23:55 by shbi              #+#    #+#             */
/*   Updated: 2023/01/03 05:48:42 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event()
{
	return 0;
}

void	minishell_loop(t_env **menv)
{
	char	*line;
	t_list	*tokens;
	t_list	*cmds;
	v_glob.exit_status = 0;
	v_glob.expand_heredoc = 0;
	while (1)
	{
		rl_catch_signals = 0;
		v_glob.heredoc_exit = 0;
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, SIG_IGN);
		tokens = NULL;
		line = NULL;
		cmds = NULL;
		line = readline("minishell-$ ");
		v_glob.heredoc_exit = 1;
		rl_event_hook = event;
		signal(SIGINT, &signal_handler);
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		tokens = get_tokens(line, *menv);
		free(line);
		if (!tokens || !check_grammar(tokens))
		{
			// v_glob.exit_status = 2;
		//lst_del(&token_lst, token_del);
			free_tokens(tokens);
		}
		else
		{
       		tokens = ft_lst_del_first(tokens);
			cmds = get_cmds(tokens, *menv);
			free_tokens(tokens);
			if(!v_glob.heredoc_exit)
				continue;
			// print_list(cmds);
			signal(SIGINT, SIG_IGN);
			execution(menv, cmds, ft_lstsize(cmds));
			free_cmds(cmds);
		}
	}
}
