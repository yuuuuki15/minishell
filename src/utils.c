/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:25:12 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/25 22:34:05 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Frees all strings in an array and the array itself.
 * @param array char**: The array of strings to be freed.
 */
void	ft_free_tab(char **array)
{
	int	i;

	i = -1;
	if (array == NULL)
		return ;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}

/**
 * Allocates and returns a key from a string up to the first equal sign.
 * @param str char*: The string to extract the key from.
 * @return char*: The allocated key string or NULL on allocation failure.
 */
char	*ft_get_key(char *str)
{
	char	*ret;

	ret = ft_substr(str, 0, ft_strchr(str, '=') - str);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

/**
 * Returns the value after the first equal sign in a string.
 * @param str char*: The string to extract the value from.
 * @return char*: The allocated value string or NULL on allocation failure.
 */
char	*ft_get_value(char *str)
{
	char	*ret;
	int		start;
	int		len;

	start = (ft_strchr(str, '=') - str) + 1;
	len = ft_strlen(str) - start;
	ret = ft_substr(str, start, len);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

/**
 * Sets all elements of an integer array to zero.
 * @param in_quotes int*: The array to be zeroed.
 * @param len int: The length of the array.
 */
void	zero_array(int *in_quotes, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		in_quotes[i] = 0;
		i++;
	}
}

void	ft_reset_fd(t_shell *shell)
{
	shell->in_fd = STDIN_FILENO;
	shell->out_fd = STDOUT_FILENO;
}
