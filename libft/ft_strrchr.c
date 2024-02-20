/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:28:21 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:47:20 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// return pointer to last occurrance of c
char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	int		i;

	i = 0;
	p = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			p = (char *)&s[i];
		i++;
	}
	if ((char)c == '\0')
		p = (char *)&s[i];
	return (p);
}
