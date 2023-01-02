#include "minishell.h"

int find_dollar(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while(str[i])
    {
        if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

char *get_kw_dq(t_env *menv,char *str,int *i)
{
    t_string *dst;
    char *value;

    value = NULL;
    v_glob.g_expand_dq = 0;
    dst = new_string("");
    (*i)++;
    while(str[(*i)] && ft_isalnum(str[(*i)]))
    {
        dst = str_append(dst, str[(*i)]);
        (*i)++;
    }
    if (find_value_with_key(menv, dst->content) != NULL)
    {
        value = find_value_with_key(menv, dst->content);
        return (value);
    }
    else
    {
        v_glob.g_expand_dq = 1;
        return (ft_substr(str, *i, ft_strlen(str)));
    }
    return (NULL);
}

char *get_kw(t_env *menv,char *str,int *i)
{
    t_string *dst;
    char *value;

    value = NULL;
    dst = new_string("");
    (*i)++;
    while(str[(*i)] && str[(*i)] != ' ' && str[(*i)] != '\'')
    {
        dst = str_append(dst, str[(*i)]);
        (*i)++;
    }
    if (find_value_with_key(menv, dst->content) != NULL)
    {
        value = find_value_with_key(menv, dst->content);
        return (value);
    }
    return (NULL);
}

t_string *expand_path_dq(t_env *menv,t_string *dst)
{
    char	*word;
    int     i;
    t_string *key;
    t_string *str = NULL;

    i = 0;
	key = new_string(NULL);
    str = new_string("");
    word = ((t_string *)dst)->content;
    while(word[i] != '\0' && i < (int)((t_string *)dst)->size)
    {
        if(word[i]== '$' && ft_strchr("\0\r\t\f\v ", word[i + 1]))
            return (str_append(str, '$'));
        else if (word[i]== '$')
        {
            key->content = get_kw_dq(menv,word, &i);
            if(key->content == NULL)
                return (free_string(&str) , new_string(""));
            if (v_glob.g_expand_dq == 1)
                return (v_glob.g_expand_dq = 0, str_concate(str,key->content));
            str = str_concate(str, ((const char *)key->content));
            if (!ft_strchr("\r\t\0\f\v|><\"",word[i]))
                str = str_append(str, word[i]);
        }
        else
            str = str_append(str, word[i]);
        i++;
    }
    return (str);
}

// t_string *expand_path(t_env *menv,t_string *dst)
// {
//     char	*word;
//     int     i;
//     t_string *key;
//     t_string *str = NULL;
//     char *old_str = NULL;
//     int check = 0;

//     i = 0;
// 	key = new_string(NULL);
//     if (find_dollar(((t_string *)dst)->content) == 1)
//     {
//         str = new_string("");
//         word = ((t_string *)dst)->content;
//         old_str = ((t_string *)dst)->content;
//         while(word[i] != '\0' && i < (int)((t_string *)dst)->size)
//         {
//             if (word[i]== '$')
//             {
//                 check = 1;
//                 key->content = get_kw(menv,word, &i);
//                 if(key->content == NULL)
//                 {
//                     while (word[i] != ' ' && word[i] != '\t' && word[i] != '\r' && word[i] != '\f' && word[i] != '\v' &&  word[i] && word[i] != '|' && word[i] != '>' && word[i] != '<' && word[i] != '\'' && word[i] != '"')
//                     {
//                         str = str_append(str, word[i]);
//                     }
//                     return (dst);
//                 }
//                 str = str_concate(str, ((const char *)key->content));
//             }
//             else
//                 str = str_append(str, word[i]);
//             i++;
//         }
//     }
//     return (str);
// }


// char *get_kw(t_env *menv,char *str,int i)
// {
//     t_string *dst;
//     char *value;

//     value = NULL;
//     dst = new_string("");
//     (*i)++;
//     while(str[(*i)] && str[(*i)] != ' ')
//     {
//         dst = str_append(dst, str[(*i)]);
//         if (find_value_with_key(menv, dst->content) != NULL)
//         {
//             value = find_value_with_key(menv, dst->content);
//             return (value);
//         }
//         (*i)++;
//     }
//     return (NULL);
// }

// t_string    *add_expand_path(t_env *menv, t_list *tmp,t_string *str,int *check)
// {
//     char    *word;
//     // t_string *key;
//     int         i;

//     i = 0;
//     // key = NULL;
//     word = ((t_token *)tmp->content)->value;
//     while(word[i] != '\0')
//     {
//         if (word[i]== '$')
//         {
//             *check = 1;
//             // key->content = ;
//             str = str_concate(str, ((const char *)get_kw(menv,word, &i)));
//         }
//         else
//             str = str_append(str, word[i]);
//         i++;
//     }
//     return (str);
// }

// void    check_expand_path(t_env *menv, t_list *tmp)
// {
//     t_string *str;
//     int check;

//     check = 0;
//     if ((((t_token *)tmp->content)->type == TOK_WORD || ((t_token *)tmp->content)->type == TOK_DQUOTE) && find_dollar(((t_token *)tmp->content)->value))
//     {
//         str = new_string(NULL);
//         str = add_expand_path(menv, tmp, str, &check);
//     }
//     if (check == 1)
//         ((t_token *)tmp->content)->value = ((t_string *)str)->content;
// }

// t_list *expand_path(t_env *menv,t_list *tokens)
// {
//     t_list  *tmp;

//     tmp = tokens;
//     while (tmp && ((t_token *)tmp->content)->type != TOK_EOL)
//     {
//         check_expand_path(menv, tmp);
//         tmp = tmp->next;
//     }
//     return (tokens);
// }