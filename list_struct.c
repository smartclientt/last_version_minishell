/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:57:07 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/05 12:00:23 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, e_token type)
{
	t_token	*token;
	size_t	len;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = (char *)malloc((ft_strlen(value) + 1) * sizeof(char));
	if (!token->value)
		return (NULL);
	len = (ft_strlen(value) + 1);
	ft_memmove(token->value, value, len);
	return (token);
}

t_list	*new_node(void *content)
{
	t_list	*p;

	p = (t_list *) malloc(sizeof(t_list));
	if (p == NULL)
		return (NULL);
	(*p).content = content;
	(*p).next = NULL;
	return (p);
}

void	print_list(t_list *tokens)
{
	t_list	*tmp;
	t_list	*red;
	int		i;

	tmp = tokens;
	while (tmp)
	{
		printf("#############\n");
		i = 0;
		while (((t_cmd *)tmp->content)->args[i] != NULL)
		{
			printf("ards===%s\n", ((t_cmd *)tmp->content)->args[i]);
			red = ((t_cmd *)tmp->content)->redirs;
			i++;
		}
		while (red)
		{
			printf("red===%s\n", ((t_redir *)red->content)->filepath);
			red = red->next;
		}
		printf("#############\n");
		tmp = tmp->next;
	}
}

void	print_list_tokens(t_list *tokens)
{
	t_list	*tmp;
	char	*c;
	t_token	*p;

	tmp = tokens;
	while (tmp && tmp->content)
	{
		p = ((t_token *)tmp->content);
		c = p->value;
		printf("[%s]", c);
		tmp = tmp->next;
	}
	printf("\n");
}
