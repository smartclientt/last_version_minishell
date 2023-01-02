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

t_string    *add_expand(t_string *dst)
{
    t_string *str;
    char *word;
    int     i;

    i = 0;
    str = new_string("");
    word = dst->content;
    while(word[i] != '\0')
    {
        if (word[i]== '$' && word[i + 1] == '?')
        {
            str = str_concate(str, ((const char *)ft_itoa(v_glob.exit_status % 255)));
            i++;
        }
        else
            str = str_append(str, word[i]);
        i++;
    }
    return (str);
}

t_string    *check_expand_status(t_string *dst)
{
    return (add_expand(dst));
}

// t_list *expand_exit_status(t_list *tokens)
// {
//     t_list  *tmp;

//     tmp = tokens;
//     while (tmp && ((t_token *)tmp->content)->type != TOK_EOL)
//     {
//         check_expand(tmp);
//         tmp = tmp->next;
//     }
//     return (tokens);
// }