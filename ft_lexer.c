/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:00:57 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 08:52:20 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string	*get_word_dq(t_env *menv, char *str, int *i)
{
	t_string	*dst;

	dst = new_string("");
	(*i)++;
	while (str[*i] != '"')
	{
		dst = str_append(dst, str[*i]);
		(*i)++;
	}
	if (find_dollar_status(dst->content))
		dst = check_expand_status(dst);
	else if (find_dollar(((t_string *)dst)->content) == 1)
		dst = expand_path_dq(menv, dst);
	(*i)++;
	// if (!dst->content || !dst)
	//     return (NULL);
	return (dst);
}

t_string	*get_word(t_env *menv, char *str, int *i)
{
	t_string	*dst;

	dst = new_string("");
	while (!ft_strchr("\r\t\f\v>< \"' ", str[*i]) && str[*i] != '|'
		&& str[*i] != '\0' && ((*i) < (int)ft_strlen(str)))
	{
		dst = str_append(dst, str[*i]);
		(*i)++;
	}
	while (find_dollar(((t_string *)dst)->content) == 1)
	{
		if (find_dollar_status(dst->content))
			dst = check_expand_status(dst);
		else if (find_dollar(((t_string *)dst)->content) == 1)
			dst = expand_path_dq(menv, dst);
	}
	if (!dst->content)
		return (free_string(&dst), NULL);
	return (dst);
}

t_string	*get_word_sq(t_env *menv, char *str, int *i)
{
	t_string	*dst;

	(void)menv;
	dst = new_string("");
	(*i)++;
	while (str[*i] != '\'')
	{
		dst = str_append(dst, str[*i]);
		(*i)++;
	}
	(*i)++;
	return (dst);
}

char	*again(t_env *menv, char *str, int *i)
{
	char		*ret;
	t_string	*dst;
	char		*tmp;

	tmp = ft_strdup("");
	ret = NULL;
	dst = NULL;
	while (!ft_strchr("\r\t\f\v>< \0", str[*i]) && str[*i] != '|'
		&& (*i) < ((int)ft_strlen(str)) && str[*i] != ' ')
	{
        // printf("--%c--(%d)",str[*i], *i);
		if (str[*i] == '"')
			dst = get_word_dq(menv, str, i);
		else if (str[*i] == '\'')
			dst = get_word_sq(menv, str, i);
		else
			dst = get_word(menv, str, i);
		// printf("%s\t%p\t%p\N",dst->content, dst->content, dst);
        // if (dst == NULL)
        //     return (NULL);
		if (dst && dst->content)
			ret = ft_strjoin(tmp, ((t_string *)dst)->content);
		free_string(&dst);
		free(tmp);
		tmp = ret;
	}
	return (free_string(&dst), ret);
}

char	*new_word_v2(t_env *menv, char *str, int *i)
{
	char		*mm;

	mm = NULL;
	if (!ft_strchr("\r\t\f\v\0|>< ", str[*i]) && (*i) < ((int)ft_strlen(str)))
		mm = again(menv, str, i);
	return (mm);
}

void	ft_check_quotes_utils(char *str, int *i, int *sq, int  *dq)
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

int	check_quotes(char *str)
{
	int	dq;
	int	sq;
	int	i;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] && ((size_t)i < ft_strlen(str)))
	{
		ft_check_quotes_utils(str, &i, &sq, &dq);
		i++;
	}
	if ((sq % 2) == 1 || (dq % 2) == 1)
	{
		write(2, "Error, unclosed quotes!\n", 24);
		return (1);
	}
	return (0);
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
			v_glob.expand_heredoc = 1;
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

t_list	*get_tokens(char *str ,t_env *menv)
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
