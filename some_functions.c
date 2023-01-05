/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 00:41:44 by shbi              #+#    #+#             */
/*   Updated: 2023/01/05 12:39:42 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_red_(char *path, e_token type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->filepath = path;
	redir->type = type;
	return (redir);
}

void	ft_gets(t_list **tp, t_list **red_list, t_env *menv)
{
	t_list	*tmp;

	tmp = *tp;
	while (((t_token *)tmp->content)->type == TOK_RINPUT
		|| ((t_token *)tmp->content)->type == TOK_ROUTPUT
		|| ((t_token *)tmp->content)->type == TOK_DRINPUT
		|| ((t_token *)tmp->content)->type == TOK_DROUTPUT)
	{
		if (((t_token *)tmp->content)->type == TOK_DRINPUT)
			ft_lstadd_back(red_list, new_node(new_red_(ft_heredocs(
							((t_token *)tmp->next->content)->value, menv),
						((t_token *)tmp->content)->type)));
		else
			ft_lstadd_back(red_list, new_node(new_red(
						((t_token *)tmp->next->content)->value,
						((t_token *)tmp->content)->type)));
		tmp = tmp->next->next;
	}
	*tp = tmp;
}

void	ft_get_cmds(t_list **tokens,
	t_list **red_list, t_vector **arg, t_env *menv)
{
	t_list	*tmp;

	tmp = *tokens;
	while (((t_token *)tmp->content)->type != TOK_PIPE
		&& ((t_token *)tmp->content)->type != TOK_EOL)
	{
		if (((t_token *)tmp->content)->type == TOK_WORD
			|| ((t_token *)tmp->content)->type == TOK_DQUOTE
			|| ((t_token *)tmp->content)->type == TOK_SINQTE)
		{
			vec_append(*arg, ((t_token *)tmp->content)->value);
			tmp = tmp->next;
		}
		ft_gets(&tmp, red_list, menv);
	}
	*tokens = tmp;
}

t_list	*get_cmds(t_list *tokens, t_env *menv)
{
	t_list		*tmp;
	t_list		*cmds;
	t_list		*red_list;
	t_vector	*arg;
	//(void)menv;

	cmds = NULL;
	tmp = tokens;
	while (((t_token *)tmp->content)->type != TOK_EOL
		&& tmp->next != NULL)
	{
		red_list = NULL;
		arg = new_vector(NULL);
		ft_get_cmds(&tmp, &red_list, &arg, menv);
		ft_lstadd_back(&cmds, new_node(
				new_cmd(arg->content, red_list)));
		free(arg);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (cmds);
}
