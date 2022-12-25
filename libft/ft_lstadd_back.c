/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shbi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:14:09 by shbi              #+#    #+#             */
/*   Updated: 2021/11/22 11:13:14 by shbi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*pl;
	int		i;

	i = 0;
	if (*lst && new)
	{
		pl = *lst;
		while (i < ft_lstsize(*lst) - 1)
		{
			pl = pl->next;
			i++;
		}
		pl->next = new;
	}
	else
		*lst = new;
}
