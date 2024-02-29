/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:26:15 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:38:48 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// allocates memory and duplicates a string
char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;
	int		s_len;

	s_len = ft_strlen(s);
	cpy = (char *) malloc ((s_len + 1) * sizeof(char));
	if (cpy == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
