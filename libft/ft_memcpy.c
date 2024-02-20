/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:39:13 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:24:14 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copies n entries of a pointer to the start of another pointer
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*s;
	size_t			i;

	p = dest;
	s = (unsigned char *)src;
	if (s == NULL && p == NULL && n > 0)
		return (NULL);
	if (dest == NULL && n > 0)
		p[42] = 42;
	i = 0;
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
	return (dest);
}
