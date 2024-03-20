/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:38:24 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:38:20 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks the content of a file for redirection purposes.
 * @param file char*: The file name to check.
 * @param shell t_shell*: The shell instance for updating exit status.
 * @return int: Returns 1 if the file content is invalid, otherwise 0.
 * @error If the file content is empty or only spaces, prints an error message
 * and sets the shell's exit status to 2.
 */
int	check_file(char *file, t_shell *shell)
{
	char		*temp;

	temp = ft_strtrim(file, " ");
	if (ft_strcmp(temp, "") == 0)
	{
		ft_putendl_fd("unaccepted token", STDERR_FILENO);
		shell->exit_status = 2;
		free (temp);
		return (1);
	}
	free (temp);
	return (0);
}
