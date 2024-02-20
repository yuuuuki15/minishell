/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:37:16 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/15 11:40:28 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// allocates memory and sticks two strings together
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	l1;
	size_t	l2;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	new = (char *) malloc ((l1 + l2 + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		new[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		new[i] = s2[i - l1];
		i++;
	}
	new[i] = '\0';
	return (new);
}
