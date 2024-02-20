/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:16:01 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/16 10:07:41 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// allocates null memory for a pointer checking for negative size and nmemb
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	tot;

	tot = nmemb * size;
	if (size != 0 && nmemb != tot / size)
		return (NULL);
	ptr = (void *) malloc (tot);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, tot);
	return (ptr);
}
