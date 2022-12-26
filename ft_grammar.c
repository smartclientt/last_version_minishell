#include "minishell.h"

int	check_rules(e_token prv, e_token cur)
{
	return ((cur == TOK_PIPE && prv == TOK_START)
		|| (cur == TOK_EOL && prv != TOK_WORD)
		|| (cur != TOK_WORD && prv != TOK_WORD && prv != TOK_START));
}

int	check_grammar(t_list *tokens)
{
	t_list	*ptr;
	t_token	*cur;
	t_token	*prv;

	ptr = tokens;
	while (ptr->next != NULL)
	{
		cur = (t_token *)ptr->next->content;
		prv = (t_token *)ptr->content;
		if (check_rules(prv->type, cur->type))
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, (t_token *)cur->value, ft_strlen((const char *)((t_token *)cur->value)));
			write(2, "'\n", 2);
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}
