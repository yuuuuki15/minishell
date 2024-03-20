/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit@student.42.fr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:57:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/09 12:00:18 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints an error message to STDERR and exits the program with status 1.
 * @param error_message char*: The error message to be printed.
 */
void	ft_error(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(1);
}
