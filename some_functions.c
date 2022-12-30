/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 00:41:44 by shbi              #+#    #+#             */
/*   Updated: 2022/12/29 18:27:36 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir *new_red(char *path, e_token type)
{
    t_redir *redir;

    redir = (t_redir *)malloc(sizeof(t_redir));
    if (redir == NULL)
        return (NULL);
    redir->filepath = path;
    redir->type = type;
    return (redir);
}

t_cmd   *new_cmd(char **args, t_list *redirs)
{
    t_cmd   *cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = args;
    cmd->fdin = 0;
    cmd->fdout = 1;
    cmd->redirs = redirs;
    return (cmd);
}

t_list  *get_cmds(t_list *tokens)
{
    t_list *tmp;
    t_list  *cmds;
    t_list  *red_list;
    t_vector *arg;

    cmds = NULL;
    tmp = tokens;
    while(((t_token *)tmp->content)->type != TOK_EOL && tmp->next != NULL)
    {
        red_list = NULL;
        arg = new_vector(NULL);
        while (((t_token *)tmp->content)->type == TOK_WORD  || ((t_token *)tmp->content)->type == TOK_DQUOTE 
            || ((t_token *)tmp->content)->type == TOK_SINQTE)
        {
            arg = vec_append(arg, ((t_token *)tmp->content)->value);
            tmp = tmp->next;
        }
        while (((t_token *)tmp->content)->type == TOK_RINPUT || ((t_token *)tmp->content)->type == TOK_ROUTPUT 
            || ((t_token *)tmp->content)->type == TOK_DRINPUT || ((t_token *)tmp->content)->type == TOK_DROUTPUT)
        {
            if (((t_token *)tmp->content)->type == TOK_DRINPUT)
                ft_lstadd_back(&red_list, new_node(new_red(ft_heredocs(((t_token *)tmp->next->content)->value), ((t_token *)tmp->content)->type)));
            else
                ft_lstadd_back(&red_list, new_node(new_red(((t_token *)tmp->next->content)->value, ((t_token *)tmp->content)->type)));
                //printf("%s\n", (red_list->content));
            tmp = tmp->next->next;
        }
        ft_lstadd_back(&cmds, new_node(new_cmd(arg->content, red_list)));
        if (tmp->next == NULL)
            break;
        tmp = tmp->next;
    }
    //free(tokens);
    //print_list(cmds);
    return (cmds);
}