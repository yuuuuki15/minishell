/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:58:14 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:42:04 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// add one string to the end of another
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	j;
	size_t	s_len;

	if (size == 0 && dst == NULL)
		return (0);
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	j = 0;
	if (d_len < size - 1 && size > 0)
	{
		while ((src[j] != '\0') && (d_len + j < size - 1))
		{
			dst[d_len + j] = src[j];
			j++;
		}
		dst[d_len + j] = '\0';
	}
	if (d_len >= size)
		return (size + s_len);
	return (d_len + s_len);
}
