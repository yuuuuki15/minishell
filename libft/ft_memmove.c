/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:03:12 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:24:50 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy an overlapping part of an array to the same array if needed
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*s;
	size_t			i;

	p = dest;
	s = (unsigned char *)src;
	if ((p == NULL) && (s == NULL) && n > 0)
		return (NULL);
	if (dest == NULL && n > 0)
		p[42] = 42;
	if ((s < p) && (p < s + n))
	{
		while (n--)
			p[n] = s[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			p[i] = s[i];
			i++;
		}
	}
	return (dest);
}
