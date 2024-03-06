/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:25:12 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/29 14:38:29 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param char** array
 *
 * This function takes an array of string that has been allocated by
 * alloc function, and frees all the strings and an array.
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
 * @param char* str
 * @return char* key
 *
 * This function allocates memory for the string up to the first
 * equal sign found as a key and returns it.
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
 * @param char* str
 * @return char* value
 *
 * This function returns the value of the first string found after the
 * equal sign.
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
