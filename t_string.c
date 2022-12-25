#include "minishell.h"

t_string *new_string(const char *str)
{
    t_string *new;
    
    new = (t_string *)malloc(sizeof(t_string));
    if (new == NULL)
        return (NULL);
    if (str == NULL)
    {
        new->content = NULL;
        new->size = 0;
    }
    else
    {
        new->size = ft_strlen(str);
        new->content = (char *)malloc((new->size + 1) * sizeof(char));
        strncpy(new->content, str, new->size + 1);
    }
    return (new);
}

t_string *str_concate(t_string *dst, const char *str)
{
    char *tmp_content;
    size_t tmp_size;
    
    tmp_size = dst->size + ft_strlen(str);
    tmp_content = (char *)malloc((tmp_size + 1) * sizeof(char));
    if (tmp_content == NULL)
    {
        free_string(&dst);
        dst = new_string(NULL);
        return (dst);
    }
    if (dst->content)
        strncpy(tmp_content, dst->content, tmp_size + 1);
    strncat(tmp_content, str, tmp_size + 1);
    free_string(&dst);
    dst = new_string(NULL);
    dst->content = tmp_content;
    dst->size = tmp_size;
    return (dst);
}

t_string *str_append(t_string *dst, char c)
{
    char *tmp_content;
    size_t tmp_size;
    
    tmp_size = dst->size + 1;
    tmp_content = (char *)malloc((tmp_size + 1) * sizeof(char));
    if (tmp_content == NULL)
    {
        free_string(&dst);
        dst = new_string(NULL);
        return (dst);
    }
    if (dst->content)
        strncpy(tmp_content, dst->content, tmp_size + 1);
    tmp_content[tmp_size - 1] = c;
    tmp_content[tmp_size] = '\0';
    free_string(&dst);
    dst = new_string(NULL);
    dst->content = tmp_content;
    dst->size = tmp_size;
    return (dst);
}

void free_string(t_string **str)
{
    if (str)
    {
        if (*str && (*str)->content)
            free((*str)->content);
        if (*str)
            free(*str);
        *str = NULL;
    }
}

// #include <stdio.h>

// int main()
// {
//     t_string *str = new_string("Youness");
//     printf("[%s]\n", str->content);
//     str_append(str, '!');
//     printf("[%s]\n", str->content);
//     str_concate(str, " Hello there!");
//     printf("[%s]\n", str->content);
//     free_string(&str);
//     printf("str is NULL : %d\n", str == NULL);
//     while (1)
//         ;
//     return (0);
// }