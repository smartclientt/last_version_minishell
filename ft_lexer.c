#include "minishell.h"


int	ft_lstsize(t_list *lst)
{
	int		c;
	t_list	*pl;

	c = 0;
	pl = lst;

	while (pl)
	{	
		pl = pl->next;
		c++;
	}
	return (c);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*pl;
	int		i;

	i = 0;
	int size = ft_lstsize(*lst);
	if (*lst && new)
	{
		pl = *lst;
		
		while (i < size - 1)
		{
			pl = pl->next;
			i++;
		}
		pl->next = new;
	}
	else
		*lst = new;
}

char *new_word(char *str , int *i)
{
    t_string *dst;
    char *ret;
    dst = new_string(NULL);
    while(str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\r' && str[*i] != '\f' && str[*i] != '\v' &&  str[*i])
    {
        dst = str_append(dst, str[*i]);
        (*i)++;
    }
    ret = dst->content;
    free(dst);
    return (ret);
}

char    *ft_dquote(char *str,int *i)
{
    t_string *dst;
    char *ret;

    (*i)++;
    dst = new_string(NULL);
    while(str[*i] != '"')
    {
        dst = str_append(dst, str[*i]);
        (*i)++;
    }
    ret = dst->content;
    free(dst);
    return (ret);
}

char    *ft_squote(char *str,int *i)
{
    t_string *dst;
    char *ret;

    dst = new_string(NULL);
    (*i)++;
    while(str[*i] != '\'')
    {
        dst = str_append(dst, str[*i]);
        (*i)++;
    }
    ret = dst->content;
    free(dst);
    return (ret);
}

int check_quotes(char *str)
{
    int dq;
    int sq;
    int i;

    i = 0;
    sq = 0;
    dq = 0;
    while (str[i] && ((size_t)i < ft_strlen(str)))
    {
        if (str[i] == '\'')
            sq += 1;
        if (str[i] == '"')
            dq += 1;
        i++;
    }
    if ((sq % 2) == 1 || (dq % 2) == 1)
    {
        write(2, "Error, unclosed quotes!\n", 24);
        return (1);
    }
    return (0);
}

t_list  *get_tokens(char *str)
{
    t_list  *tokens = NULL;
    int     i;

    i = 0;
    if (str == NULL)
        return (NULL);
    // if (check_quotes(str))
    //     return (NULL);
    // printf("%zu", ft_strlen(str));
    while (str[i] != '\0' && i < (int)ft_strlen(str))
    {
		
        while(str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
            i++;
		if (str[i] == '|')
			ft_lstadd_back(&tokens, new_node(new_token("|", TOK_PIPE)));
		else if (str[i] == '\'')
			ft_lstadd_back(&tokens, new_node(new_token(ft_squote(str , &i), TOK_SINQTE)));
		else if (str[i] == '"')
			ft_lstadd_back(&tokens, new_node(new_token(ft_dquote(str , &i), TOK_DQUOTE)));
		else if (str[i] == '<' && str[i + 1] == '<')
		{
        	ft_lstadd_back(&tokens, new_node(new_token("<<", TOK_DRINPUT)));
            i++;
        }
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			ft_lstadd_back(&tokens, new_node(new_token(">>", TOK_DROUTPUT)));
			i++;
		}
		else if (str[i] == '<')
			ft_lstadd_back(&tokens, new_node(new_token("<", TOK_RINPUT)));
		else if (str[i] == '>')
			ft_lstadd_back(&tokens, new_node(new_token(">", TOK_ROUTPUT)));
        else
        {
            char *w = new_word(str , &i);
            ft_lstadd_back(&tokens, new_node(new_token(w, TOK_WORD)));
        }
        i++;
        // // token_parser f = get_parser(str[i]);
        // // ft_lstadd_back(&tokens, new_node(f(str, i)));
    }
    ft_lstadd_back(&tokens, new_node(new_token("EOL", TOK_EOL)));
    return (tokens);
}