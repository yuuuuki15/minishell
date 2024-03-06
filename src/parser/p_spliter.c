/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_spliter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/06 10:40:47 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// counts number of words in string based on spaces but not spaces in quotes
size_t	p_num_words(char *s)
{
	size_t	words;
	int		i;
	int		*q_check;
	int		state;

	q_check = parse_quotes(s);
	state = q_check[0];
	words = 0;
	if (ft_strlen(s) == 0)
		return (words);
	if (s[0] != ' ' || state == 1)
		words++;
	i = 1;
	while (s[i] != '\0')
	{
		if ((s[i] != ' ' && s[i - 1] == ' ' && q_check[i - 1] == 0))
			words++;
		i++;
	}
	free (q_check);
	return (words);
}

// allocates memory to make a copy of a string
char	*p_ft_strndup(char *s, size_t n)
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
size_t	p_word_length(char *s, int *q_check)
{
	size_t	len;

	len = 0;
	while ((q_check[len] == 1 || (q_check[len] == 0
				&& s[len] != ' ')) && s[len] != '\0')
		len++;
	return (len);
}

// allocates the interior strings of the array
int	p_allocate(char **a, char *s, size_t words)
{
	size_t	k;
	size_t	i;
	int		*q_check;

	q_check = parse_quotes(s);
	k = 0;
	i = 0;
	while (k < words)
	{
		if (s[i] != ' ')
		{
			if (i == 0 || (i > 0 && (s[i - 1] == ' ' && q_check[i - 1] == 0)))
			{
				a[k] = p_ft_strndup(&s[i], p_word_length(&s[i], &q_check[i]));
				if (a[k] == 0)
					return (k);
				k++;
			}
		}
		i++;
	}
	free (q_check);
	return (-1);
}

// splits a string into an array of words based on spaces nd quoted text
char	**p_spliter(char *s)
{
	char	**array;
	size_t	words;
	int		a_fail;
	int		k;

	if (s == NULL)
		return (NULL);
	words = p_num_words(s);
	array = (char **) malloc ((words + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	a_fail = p_allocate(array, s, words);
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
