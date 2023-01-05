/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop_.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:22:38 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 22:19:49 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global_var(void)
{
	g_glob.exit_status = 0;
	g_glob.expand_heredoc = 0;
}

void	signal_loop(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	print_exit(void)
{
	printf("exit\n");
	exit(0);
}

void	all_free_loop(char	*line, t_list **tokens, t_list **cmds)
{
	free(line);
	free_cmds(*cmds);
	free_tokens(*tokens);
}

void	after_check_grammer(t_env **menv, t_list **tokens, t_list **cmds)
{
	*tokens = ft_lst_del_first(*tokens);
	*cmds = get_cmds(*tokens, *menv);
	if (!g_glob.heredoc_exit)
		return ;
	signal(SIGINT, SIG_IGN);
	execution(menv, *cmds, ft_lstsize(*cmds));
}
