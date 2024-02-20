/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:36:16 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:44:23 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// allocates memory for a string and then uses *f to map old str to new
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	char	*smap;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	smap = (char *) malloc ((s_len + 1) * sizeof(char));
	if (smap == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		smap[i] = f(i, s[i]);
		i++;
	}
	smap[s_len] = '\0';
	return (smap);
}
