/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:27:02 by shbi              #+#    #+#             */
/*   Updated: 2021/11/21 23:27:57 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*head;
	t_list	*pl;

	pl = *lst;
	while (pl)
	{
		head = pl->next;
		del(pl->content);
		free(pl);
		pl = head;
	}
	*lst = NULL;
}
