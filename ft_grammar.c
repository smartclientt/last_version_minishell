#include "minishell.h"

int	check_rules(e_token prv, e_token cur)
{
	return ((cur == TOK_PIPE && prv == TOK_START)
		|| (cur == TOK_EOL && (prv != TOK_WORD && prv != TOK_DQUOTE && prv != TOK_SINQTE))
		|| ((prv != TOK_WORD && prv != TOK_DQUOTE && prv != TOK_SINQTE && prv != TOK_START
		&& cur != TOK_WORD && cur != TOK_DQUOTE && cur != TOK_SINQTE)));
}

int	check_only_red(t_list *ptr)
{

	if(ft_lstsize(ptr) == 3)
	{
		if (((t_token *)ptr->content)->type == TOK_START && ((t_token *)ptr->next->content)->type != TOK_WORD 
			&& ((t_token *)ptr->next->content)->type != TOK_DQUOTE && ((t_token *)ptr->next->content)->type != TOK_SINQTE
			&& ((t_token *)ptr->next->next->content)->type == TOK_EOL)
		{
			if (((t_token *)ptr->next->content)->type == TOK_PIPE)
				write(2, "minishell: syntax error near unexpected token `|'\n", 50);
			else
				write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
			return (0);		
		}
	}
	return (1);
}

void	check_rul(t_token *prv, t_token *cur)
{
	char *p;
	int	len;

	if ((prv->type >= 3 && prv->type <= 6) || prv->type == TOK_START)
	{
		p = cur->value;
		len = ft_strlen((const char *)((t_token *)cur->value));
	}
	else
	{
		p = prv->value;
		len = ft_strlen((const char *)((t_token *)prv->value));
	}
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, p, len);
	write(2, "'\n", 2);
}

int	check_only(t_list *ptr)
{
	t_token	*cur;
	t_token	*prv;

	while (ptr->next != NULL)
	{
		cur = (t_token *)ptr->next->content;
		prv = (t_token *)ptr->content;
		if (check_rules(prv->type, cur->type))
		{
			check_rul(prv, cur);
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

int	check_grammar(t_list *tokens)
{
	t_list	*ptr;

	ptr = tokens;
	if (ft_lstsize(ptr) <= 2)
		return (1);
	if (!check_only_red(ptr))
		return (0);
	if (!check_only(ptr))
		return (0);
	return (1);
}
