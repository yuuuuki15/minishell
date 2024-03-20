/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_spliter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:53:48 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:45:19 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Counts the number of words in a string, ignoring spaces within quotes.
 * @param s char*: The input string to count words in.
 * @return size_t: The number of words found in the string.
 */
static size_t	p_num_words(char *s)
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
	if (s[0] != ' ' || state != 0)
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

/**
 * Allocates memory and duplicates a substring from the input string.
 * @param s char*: The input string to duplicate from.
 * @param n size_t: The number of characters to duplicate.
 * @return char*: A pointer to the duplicated string.
 * @error Returns NULL if memory allocation fails.
 */
static char	*p_ft_strndup(char *s, size_t n)
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

/**
 * Determines the length of a word in a string, considering quotes.
 * @param s char*: The input string containing the word.
 * @param q_check int*: Array indicating if a character is within quotes.
 * @param i int: The starting index of the word in the string.
 * @return size_t: The length of the word.
 */
static size_t	p_word_length(char *s, int *q_check, int i)
{
	size_t	len;

	len = 0;
	while (s[i + len] != '\0' && (q_check[i + len] != 0
			|| (q_check[i + len] == 0 && s[i + len] != ' ')))
		len++;
	return (len);
}

/**
 * Allocates memory for each word in the array.
 * @param a char**: The array to allocate memory for each word.
 * @param s char*: The input string to split into words.
 * @param words size_t: The number of words to allocate memory for.
 * @return int: -1 on success, or the index of the word that failed to allocate.
 * @error Returns the index of the word that failed to allocate if any.
 */
static int	p_allocate(char **a, char *s, size_t words)
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
				a[k] = p_ft_strndup(&s[i], p_word_length(s, q_check, i));
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

/**
 * Splits a string into an array of words, considering spaces and quotes.
 * @param s char*: The input string to split.
 * @return char**: An array of strings, each being a word from the input.
 * @error Returns NULL if the input string is NULL, memory allocation fails,
 *        or word allocation fails.
 */
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
