/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:26:02 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:20:30 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// allocates memory for a new list item and inserts content
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
