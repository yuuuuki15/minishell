/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:25:12 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/23 14:30:35 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
