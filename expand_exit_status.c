#include "minishell.h"

int find_dollar_status(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '$' && str[i + 1] == '?')
            return (1);
        i++;
    }
    return (0);
}

t_string    *add_expand(t_list *tmp,t_string *str,int *check)
{
    char *word;
    int     i;

    i = 0;
    word = ((t_token *)tmp->content)->value;
    while(word[i] != '\0')
    {
        if (word[i]== '$' && word[i + 1] == '?')
        {
            *check = 1;
            str = str_concate(str, ((const char *)ft_itoa(v_glob.exit_status)));
            i++;
        }
        else
            str = str_append(str, word[i]);
        i++;
    }
    return (str);
}

void    check_expand(t_list *tmp)
{
    t_string *str;
    int check;

    check = 0;
    if ((((t_token *)tmp->content)->type == TOK_WORD || ((t_token *)tmp->content)->type == TOK_DQUOTE) && find_dollar_status(((t_token *)tmp->content)->value))
    {
        str = new_string("");
        str = add_expand(tmp, str, &check);
    }
    if (check == 1)
        ((t_token *)tmp->content)->value = ((t_string *)str)->content;
}

t_list *expand_exit_status(t_list *tokens)
{
    t_list  *tmp;

    tmp = tokens;
    while (tmp && ((t_token *)tmp->content)->type != TOK_EOL)
    {
        check_expand(tmp);
        tmp = tmp->next;
    }
    return (tokens);
}