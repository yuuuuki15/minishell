/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:47:26 by mevonuk           #+#    #+#             */
/*   Updated: 2023/11/16 10:42:19 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// counts number of words in string
size_t	num_words(char const *s, char c)
{
	size_t	words;
	int		i;

	words = 0;
	if (ft_strlen(s) == 0)
		return (words);
	if (s[0] != c)
		words++;
	i = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

// allocates memory to make a copy of a string
char	*ft_strndup(const char *s, size_t n)
{
	char	*cpy;
	size_t	i;

	cpy = (char *) malloc ((n + 1) * sizeof(char));
	if (cpy == NULL)
		return (0);
	i = 0;
	while (s[i] && i < n)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

// determines the length of a word
size_t	word_length(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

// allocates the interior strings of the array
int	allocate(char **a, char const *s, char c, size_t words)
{
	size_t	k;
	size_t	i;

	k = 0;
	i = 0;
	while (k < words)
	{
		if (s[i] != c)
		{
			if (i == 0 || (i > 0 && s[i - 1] == c))
			{
				a[k] = ft_strndup(&s[i], word_length(&s[i], c));
				if (a[k] == 0)
					return (k);
				k++;
			}
		}
		i++;
	}
	return (-1);
}

// splits a string into an array of words
char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;
	int		a_fail;
	int		k;

	if (s == NULL)
		return (NULL);
	words = num_words(s, c);
	array = (char **) malloc ((words + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	a_fail = allocate(array, s, c, words);
	if (a_fail != -1)
	{
		k = 0;
		while (k < a_fail)
		{
			free (array[k]);
			k++;
		}
		free (array);
		return (NULL);
	}
	array[words] = NULL;
	return (array);
}
