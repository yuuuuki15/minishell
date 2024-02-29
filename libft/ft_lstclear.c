/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:33:11 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:14:26 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// clears a list using *del and sets pointer to NULL
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*nex;

	if (lst == NULL || del == NULL)
		return ;
	cur = *lst;
	while (cur != NULL)
	{
		nex = cur->next;
		del(cur->content);
		free (cur);
		cur = nex;
	}
	*lst = NULL;
}
