/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:23:55 by shbi              #+#    #+#             */
/*   Updated: 2022/12/26 01:25:09 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	minishell_loop(t_env **menv)
// {
// 	(void)menv;
// 	char	*line;
// 	t_list	*tokens;
//     t_list	*cmds;
	
// 	while(1)
// 	{
// 		tokens = NULL;
// 		line = NULL;
// 		cmds = NULL;
// 		line = readline("minishell-$ ");
// 		if (ft_strcmp("exit", line))
// 			exit(0);
// 		add_history(line);
// 		tokens = get_tokens(line);
// 		tokens = expand_dollar(*menv,tokens);
// 		cmds = get_cmds(tokens);
// 		execution(menv, cmds, ft_lstsize(cmds));
// 		free(line);
// 		free(tokens);
// 		free(cmds);
// 	}
// }
