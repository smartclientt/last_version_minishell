#include "minishell.h"

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

void    token_word(t_list **tokens, char *str, int *i)
{
    char *w;
    
    w = new_word(str , i);
    ft_lstadd_back(tokens, new_node(new_token(w, TOK_WORD)));
}

void  add_tokens(t_list **tokens, char *str, int *i)
{
    if (str[(*i)] == '|')
            ft_lstadd_back(tokens, new_node(new_token("|", TOK_PIPE)));
        else if (str[(*i)] == '\'')
            ft_lstadd_back(tokens, new_node(new_token(ft_squote(str , i), TOK_SINQTE)));
        else if (str[(*i)] == '"')
            ft_lstadd_back(tokens, new_node(new_token(ft_dquote(str , i), TOK_DQUOTE)));
        else if (str[(*i)] == '<' && str[(*i) + 1] == '<')
        {
            ft_lstadd_back(tokens, new_node(new_token("<<", TOK_DRINPUT)));
            (*i)++;
        }
        else if (str[(*i)] == '>' && str[(*i) + 1] == '>')
        {
            ft_lstadd_back(tokens, new_node(new_token(">>", TOK_DROUTPUT)));
            (*i)++;
        }
        else if (str[(*i)] == '<')
            ft_lstadd_back(tokens, new_node(new_token("<", TOK_RINPUT)));
        else if (str[(*i)] == '>')
            ft_lstadd_back(tokens, new_node(new_token(">", TOK_ROUTPUT)));
        else
            token_word(tokens, str, i);
}

t_list  *get_tokens(char *str)
{
    t_list  *tokens = NULL;
    int     i;

    i = 0;
    if (str == NULL)
        return (NULL);
    while (str[i] != '\0' && i < (int)ft_strlen(str))
    {
        while(str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
            i++;
        if (str[i] == '\0')
            break;
        add_tokens(&tokens, str, &i);
        i++;
    }
    ft_lstadd_back(&tokens, new_node(new_token("newline", TOK_EOL)));
    ft_lstadd_front(&tokens, new_node(new_token("START", TOK_START)));
    return (tokens);
}