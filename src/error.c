/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:57:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/09 12:00:18 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function will print error message in STDERR and exit program with
 * status number 1
 * @param char* error_message
*/
void	ft_error(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(1);
}
