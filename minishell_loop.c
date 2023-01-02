/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:23:55 by shbi              #+#    #+#             */
/*   Updated: 2023/01/02 06:26:35 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_env **menv)
{
	char	*line;
	t_list	*tokens;
	t_list	*cmds;
	v_glob.exit_status = 0;
	while (1)
	{
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, SIG_IGN);
		tokens = NULL;
		line = NULL;
		cmds = NULL;
		line = readline("minishell-$ ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		tokens = get_tokens(line, *menv);
        tokens = ft_lst_del_first(tokens);
		print_list_tokens(tokens);
		if (!tokens || !check_grammar(tokens))
		{
			v_glob.exit_status = 258;
		//lst_del(&token_lst, token_del);
		}
		// else
		{
			cmds = get_cmds(tokens);
			print_list(cmds);
			execution(menv, cmds, ft_lstsize(cmds));
			free(line);
			free(tokens);
			free(cmds);
		}
	}
}
