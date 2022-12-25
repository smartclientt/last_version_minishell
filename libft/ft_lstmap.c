/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:42:21 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 23:43:53 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nl;
	t_list	*pl;

	if (!lst)
		return (NULL);
	pl = NULL;
	while (lst)
	{
		nl = ft_lstnew(f(lst->content));
		if (!nl)
		{
			ft_lstclear(&nl, del);
			break ;
		}
		ft_lstadd_back(&pl, nl);
		lst = lst->next;
	}
	return (pl);
}
