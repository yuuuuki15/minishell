/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:39:41 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:46:58 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// looks for a little string in a big string, checks len
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	slen;

	slen = ft_strlen(little);
	if (slen == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while ((big[i] != '\0') && (i <= len - slen))
	{
		if (ft_strncmp(big + i, little, slen) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
