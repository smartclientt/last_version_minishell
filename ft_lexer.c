#include "minishell.h"

t_string    *get_word_dq(t_env *menv,char *str, int *i)
{
    t_string    *dst;

    dst = new_string(NULL);
    (*i)++;
    while(str[*i] != '"')
    {
        //filter_quotes(str[*i], check, i);
        // if (str[*i] == '\'')
        //     v_glob.g_expand_dq = 1;
        dst = str_append(dst, str[*i]);
        (*i)++;
    }
    if (find_dollar_status(dst->content))
        dst = check_expand_status(dst);
    else if (find_dollar(((t_string *)dst)->content) == 1)
        dst = expand_path_dq(menv,dst);
    // dst = expand_exit_status(dst);
    (*i)++;
    // if (!dst->content)
    //     return (NULL);
    // check[1]++;
    return (dst);
}

t_string    *get_word(t_env *menv,char *str, int *i)
{
    t_string    *dst;

    dst = new_string(NULL);
    while(!ft_strchr("\r\t\f\v|>< \"' ",str[*i]) && str[*i] != '\0' && ((*i) <  (int)ft_strlen(str)))
    {
        //filter_quotes(str[*i], check, i);
        dst = str_append(dst, str[*i]);
        (*i)++;
    }
    if (find_dollar_status(dst->content))
        dst = check_expand_status(dst);
    else if (find_dollar(((t_string *)dst)->content) == 1)
        dst = expand_path_dq(menv,dst);
    // dst = expand_exit_status(dst);
    if (!dst->content)
        return (NULL);
    // check[1]++;
    return (dst);
}

t_string    *get_word_sq(t_env *menv, char *str, int *i)
{
    t_string    *dst;
    (void)menv;

    dst = new_string(NULL);
    // printf("[%c][%s]\n",str[*i], dst->content);
    (*i)++;
    while(str[*i] != '\'')
    {
        //filter_quotes(str[*i], check, i);
        dst = str_append(dst, str[*i]);
        (*i)++;
    }
    // if (find_dollar(((t_string *)dst)->content) == 1)
    //     dst = expand_path(menv,dst);
    // if (!dst->content)
    //     return (NULL);
    (*i)++;
    // check[0]++;
    return (dst);
}

// t_string  *get_expend(t_env *menv, char *str, int *i)
// {
//     t_string    *dst;

//     dst = new_string(NULL);;
//     while(!ft_strchr("\r\t\f\v\0|>< \"'",str[*i]) && ((*i) <  (int)ft_strlen(str)))
//     {
//         // filter_quotes(str[*i], check, i);
//         char *old_dst = NULL;
//         (*i)++;
//         while(!ft_strchr("\r\t\f\v\0|>< \"'",str[*i]) && ((*i) <  (int)ft_strlen(str) - 1) && ft_isalnum(str[(*i)]))
//         {
//             dst = str_append(dst, str[*i]);
//             (*i)++;
//         }
//         if (!dst->content)
//             return (NULL);
//         old_dst = dst->content;
//         dst = expand_path_dq(menv,dst);
//         if (!ft_strcmp(dst->content, old_dst))
//             return (dst);
//         else
//             return (NULL);
//         dst = str_append(dst, str[*i]);
//         (*i)++;
//     }
//     return (dst);
// }

char  *again(t_env *menv, char *str, int *i)
{
    char *ret = "";
    t_string *dst;

    dst = NULL;
    while (!ft_strchr("\r\t\f\0\v|>< ",str[*i]) && (*i) < ((int)ft_strlen(str)) && str[*i] != ' ')
    {
        // printf("--%c--(%d)",str[*i], *i);
        if (str[*i] == '"')
            dst = get_word_dq(menv, str, i);
        else if (str[*i] == '\'')
            dst = get_word_sq(menv, str, i);
        else
            dst = get_word(menv, str, i);
        // if (dst == NULL)
        //     return (NULL);
        if (dst && dst->content)
            ret = ft_strjoin(ret, ((t_string *)dst)->content);
        free_string(&dst);
    }
    return (ret);
}

char *new_word_v2(t_env *menv, char *str , int *i)
{
    int check[2];
    t_string *con;
    char *ret;
        char *mm = NULL;

    check[0] = 0;//sq
    check[1] = 0;//dq

    // free(dst);
    ret = NULL;
    con = new_string(NULL);
    if (!ft_strchr("\r\t\f\v\0|>< ",str[*i]) && (*i) < ((int)ft_strlen(str)))
    {
        
        mm = again(menv, str, i);
        // con = str_concate(con, mm);
    }
    // ret = ((t_string *)mm)->content;
    // if (ret == NULL)
    // {
    //     puts("hey");
    //     // break;
    // }
    return (mm);
}

void    ft_check_quotes_utils(char *str, int *i, int *sq, int  *dq)
{
    if (str[(*i)] == '\'')
    {
        *sq += 1;
        while (str[(*i)] && ((size_t)(*i) < ft_strlen(str)))
        {
            (*i)++;
            if (str[(*i)] == '\'')
                break;
        }
        if ((str[(*i)] && ((size_t)(*i) < ft_strlen(str))))
            *sq += 1;
    }
    if (str[(*i)] == '"')
        *dq += 1;
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

void    token_word(t_env *menv,t_list **tokens, char *str, int *i)
{
    char *w;

    w = new_word_v2(menv, str , i);
    if (w == NULL)
        return ;
    ft_lstadd_back(tokens, new_node(new_token(w, TOK_WORD)));
}

void    add_tokens_with(t_list **tokens, char *str, int *i)
{
    if (ft_strchr("<>",str[*i]) && ft_strchr("<>",str[(*i) + 1]))
    {
        if (str[(*i)] == '<' && str[(*i) + 1] == '<')
            ft_lstadd_back(tokens, new_node(new_token("<<", TOK_DRINPUT)));
        else if (str[(*i)] == '>' && str[(*i) + 1] == '>')
            ft_lstadd_back(tokens, new_node(new_token(">>", TOK_DROUTPUT)));
        (*i) +=2;
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

void  add_tokens(t_env *menv, t_list **tokens, char *str, int *i)
{
    if (ft_strchr("|<>",str[*i]) && str[*i] != '\0')
        add_tokens_with(tokens, str, i);
    else if (str[(*i)] == '\'')
    {    
        ft_lstadd_back(tokens, new_node(new_token(new_word_v2(menv, str , i), TOK_SINQTE)));
        //ft_lstadd_back(tokens, new_node(new_token(ft_squote(str , i), TOK_SINQTE)));
    }
    else if (str[(*i)] == '"')
    {
        char *w;
        w = new_word_v2(menv, str , i);
          if (ft_strcmp(w,""))
            return ;
        ft_lstadd_back(tokens, new_node(new_token(w, TOK_DQUOTE)));
    }
    else
        token_word(menv, tokens, str, i);
}

t_list  *get_tokens(char *str , t_env *menv)
{
    t_list  *tokens = NULL;
    int     i;

    i = 0;
    if (str == NULL)
        return (NULL);
    if (check_quotes(str))
        exit (1);
    while (str[i] != '\0' && i < (int)ft_strlen(str))
    {
        while(str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
            i++;
        if (str[i] == '\0')
            break;
        add_tokens(menv, &tokens, str, &i);
        
    }
    ft_lstadd_back(&tokens, new_node(new_token("newline", TOK_EOL)));
    ft_lstadd_front(&tokens, new_node(new_token("START", TOK_START)));
    return (tokens);
}
