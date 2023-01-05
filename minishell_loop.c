/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:23:55 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 23:27:23 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_env **menv, char *line, t_list	**tokens, t_list **cmds)
{
	*tokens = get_tokens(line, *menv);
	if (!*tokens || !check_grammar(*tokens))
		g_glob.exit_status = 258;
	else
		after_check_grammer(menv, tokens, cmds);
}

void	minishell_loop(t_env **menv)
{
	char	*line;
	t_list	*tokens;
	t_list	*cmds;

	init_global_var();
	while (1)
	{
		rl_catch_signals = 0;
		g_glob.heredoc_exit = 0;
		signal_loop();
		tokens = NULL;
		line = NULL;
		cmds = NULL;
		line = readline("minishell-$ ");
		g_glob.heredoc_exit = 1;
		rl_event_hook = event;
		signal(SIGINT, &signal_handler);
		if (!line)
			print_exit();
		add_history(line);
		minishell(menv, line, &tokens, &cmds);
		all_free_loop(line, &tokens, &cmds);
	}
}

// void	minishell_loop(t_env **menv)
// {
// 	char	*line;
// 	t_list	*tokens;
// 	t_list	*cmds;
// 	g_glob.exit_status = 0;
// 	g_glob.expand_heredoc = 0;
// 	while (1)
// 	{
// 		rl_catch_signals = 0;
// 		g_glob.heredoc_exit = 0;
// 		signal(SIGINT, &signal_handler);
// 		signal(SIGQUIT, SIG_IGN);
// 		tokens = NULL;
// 		line = NULL;
// 		cmds = NULL;
// 		line = readline("minishell-$ ");
// 		g_glob.heredoc_exit = 1;
// 		rl_event_hook = event;
// 		signal(SIGINT, &signal_handler);
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			exit(0);
// 		}
// 		add_history(line);
// 		tokens = get_tokens(line, *menv);
// 		free(line);
// 		if (!tokens || !check_grammar(tokens))
// 		{
// 			free(line);
// 			g_glob.exit_status = 258;
// 		// lst_del(&token_lst, token_del);
// 			// free_tokens(tokens);
// 		}
// 		else
// 		{
//        		tokens = ft_lst_del_first(tokens);
// 			cmds = get_cmds(tokens, *menv);
// 			// system("leaks minishell");
// 			// free_tokens(tokens);
// 			if(!g_glob.heredoc_exit)
// 				continue;
// 			// print_list(cmds);
// 			signal(SIGINT, SIG_IGN);
// 			execution(menv, cmds, ft_lstsize(cmds));
// 		}
// 			free_cmds(cmds);
// 			free_tokens(tokens);
// 	}
// }
