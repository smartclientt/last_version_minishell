#include "minishell.h"

int find_dollar(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

char *get_kw(t_env *menv,char *str,int *i)
{
    t_string *dst;
    char *value;

    value = NULL;
    dst = new_string("");
    (*i)++;
    while(str[(*i)] && str[(*i)] != ' ')
    {
        dst = str_append(dst, str[(*i)]);
        if (find_value_with_key(menv, dst->content) != NULL)
        {
            value = find_value_with_key(menv, dst->content);
            return (value);
        }
        (*i)++;
    }
    return (NULL);
}

t_list *expand_dollar(t_env *menv,t_list *tokens)
{
    t_list  *tmp;
    char	*word;
    int     i;
    t_string *key;
    t_string *str;
    int check = 0;

    i = 0;
    tmp = tokens;
	key = NULL;
    while (tmp && ((t_token *)tmp->content)->type != TOK_EOL)
    {
        if ((((t_token *)tmp->content)->type == TOK_WORD || ((t_token *)tmp->content)->type == TOK_DQUOTE) && find_dollar(((t_token *)tmp->content)->value))
        {
            str = new_string("");
            word = ((t_token *)tmp->content)->value;
            while(word[i] != '\0')
            {
                if (word[i]== '$')
                {
                    check = 1;
                    key->content = get_kw(menv,word, &i);
                    if(key->content == NULL)
                        return (free_string(&str) , tokens);
                    str = str_concate(str, ((const char *)key->content));
                }
                else
                    str = str_append(str, word[i]);
                // printf("%s----%d\n",word + i + 1, i);
                //printf("[%s]\n", str->content);
                i++;
            }
        }
        if (check == 1)
            ((t_token *)tmp->content)->value = ((t_string *)str)->content;
        check = 0;
    //     char *p = ((t_token *)tmp->content)->value;
    //     printf("%s\n", p);
    // printf("**%d\n", ft_lstsize(tmp));
        tmp = tmp->next;
    }
    return (tokens);
}