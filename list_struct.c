#include "minishell.h"

t_token *new_token(char *value, e_token type)
{
    t_token *token;
    size_t  len;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = (char *)malloc((ft_strlen(value) + 1) * sizeof(char));
    if (!token->value)
        return (NULL);
    len = (ft_strlen(value) + 1);
    ft_memmove(token->value, value, len);
    return (token);
}

t_list	*new_node(void *content)
{
	t_list	*p;

	p = (t_list *) malloc(sizeof(t_list));
	if (p == NULL)
		return (NULL);
	(*p).content = content;
	(*p).next = NULL;

	return (p);
}

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*tmp;

// 	tmp = *lst;
// 	if (new)
// 	{
// 		if (tmp && tmp->content != NULL)
// 		{	
// 			while (tmp->next != NULL)
// 			{
// 				tmp = tmp->next;
// 			}
// 			tmp->next = new;
// 		}
// 		else
// 			*lst = new;
// 	}
//     //printf("add back\n");
//     //printf("%s\n",((t_token *)(new)->content)->value);
// }

void    print_list(t_list *tokens)
{
    t_list  *tmp;
    t_list  *red;
    int i;

    tmp = tokens;
    while (tmp)
    {
        printf("#############\n");
        i = 0;
        while (((t_cmd *)tmp->content)->args[i] != NULL)
        {
            printf("ards===%s\n", ((t_cmd *)tmp->content)->args[i]);
            red = ((t_cmd *)tmp->content)->redirs;
            i++;
        }
        while (red)
        {    
            printf("red===%s\n", ((t_redir *)red->content)->filepath);
            red = red->next;
        }
        printf("#############\n");
        //printf("value:[%s]\t type:[%d]\n",((t_token *)tmp->content)->value, ((t_token *)tmp->content)->type);
        tmp = tmp->next;
    }
    //printf("value:[%s]\t type:[%d]\n",((t_token *)tmp->content)->value, ((t_token *)tmp->content)->type);
}

void    print_list_tokens(t_list *tokens)
{
    t_list  *tmp;


    tmp = tokens;
    while (tmp && tmp->content)
    {
        t_token *p = ((t_token *)tmp->content);
        char *c = p->value;
        printf("[%s]", c);
        tmp = tmp->next;
    }
    printf("\n");
}
