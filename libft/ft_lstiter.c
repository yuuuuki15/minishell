/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:41:45 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:17:59 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// iterates over a list enacting *f on the list contents
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	if (lst == NULL || f == NULL)
		return ;
	ptr = lst;
	while (ptr != NULL)
	{
		f(ptr->content);
		ptr = ptr->next;
	}
}
