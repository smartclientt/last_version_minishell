/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:23:55 by shbi              #+#    #+#             */
/*   Updated: 2022/12/26 12:24:19 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_env **menv)
{
	(void)menv;
	char	*line;
	t_list	*tokens;
    t_list	*cmds;
	
	while(1)
	{
		tokens = NULL;
		line = NULL;
		cmds = NULL;
        v_glob = (t_glob){0};
		line = readline("minishell-$ ");
		if (ft_strcmp("exit", line))
			exit(0);
		add_history(line);
		tokens = get_tokens(line);
        tokens = ft_lst_del_first(tokens);
		tokens = expand_path(*menv,tokens);
        tokens = expand_exit_status(tokens);
        //print_list_tokens(tokens);
		cmds = get_cmds(tokens);
        //print_list(cmds);
		execution(menv, cmds, ft_lstsize(cmds));
		free(line);
		free(tokens);
		free(cmds);
	}
}
