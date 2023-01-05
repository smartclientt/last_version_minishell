/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:00:57 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 12:37:41 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quotes_utils(char *str, int *i, int *sq, int *dq)
{
	if (str[(*i)] == '\'')
	{
		*sq += 1;
		while (str[(*i)] && ((size_t)(*i) < ft_strlen(str)))
		{
			(*i)++;
			if (str[(*i)] == '\'')
				break ;
		}
		if ((str[(*i)] && ((size_t)(*i) < ft_strlen(str))))
			*sq += 1;
	}
	if (str[(*i)] == '"')
		*dq += 1;
}

void	token_word(t_env *menv, t_list **tokens, char *str, int *i)
{
	char	*w;

	w = new_word_v2(menv, str, i);
	if (w == NULL)
		return ;
	ft_lstadd_back(tokens, new_node(new_token(w, TOK_WORD)));
	free(w);
}

void	add_tokens_with(t_list **tokens, char *str, int *i)
{
	if ((str[*i] == '>' && str[(*i) + 1] == '>')
		|| (str[*i] == '<' && str[(*i) + 1] == '<'))
	{
		if (str[(*i)] == '<' && str[(*i) + 1] == '<')
		{
			ft_lstadd_back(tokens, new_node(new_token("<<", TOK_DRINPUT)));
			g_glob.expand_heredoc = 1;
		}
		else if (str[(*i)] == '>' && str[(*i) + 1] == '>')
			ft_lstadd_back(tokens, new_node(new_token(">>", TOK_DROUTPUT)));
		(*i) += 2;
	}
	else
	{
		if (str[(*i)] == '|')
			ft_lstadd_back(tokens, new_node(new_token("|", TOK_PIPE)));
		else if (str[(*i)] == '<')
			ft_lstadd_back(tokens, new_node(new_token("<", TOK_RINPUT)));
		else if (str[(*i)] == '>')
			ft_lstadd_back(tokens, new_node(new_token(">", TOK_ROUTPUT)));
		(*i)++;
	}
}

void	add_tokens(t_env *menv, t_list **tokens, char *str, int *i)
{
	char	*w;

	w = NULL;
	if (ft_strchr("|<>", str[*i]) && str[*i] != '\0')
		add_tokens_with(tokens, str, i);
	else if (str[(*i)] == '\'')
	{
		w = new_word_v2(menv, str, i);
		ft_lstadd_back(tokens, new_node(new_token(
					w, TOK_SINQTE)));
	}
	else if (str[(*i)] == '"')
	{
		w = new_word_v2(menv, str, i);
		ft_lstadd_back(tokens, new_node(new_token(w, TOK_DQUOTE)));
	}
	else
		token_word(menv, tokens, str, i);
	free(w);
}

t_list	*get_tokens(char *str, t_env *menv)
{
	t_list	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	if (str == NULL)
		return (NULL);
	if (check_quotes(str))
		return (0);
	while (str[i] != '\0' && i < (int)ft_strlen(str))
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\v')
			i++;
		if (str[i] == '\0')
			break ;
		add_tokens(menv, &tokens, str, &i);
	}
	ft_lstadd_back(&tokens, new_node(new_token("newline", TOK_EOL)));
	ft_lstadd_front(&tokens, new_node(new_token("START", TOK_START)));
	return (tokens);
}
