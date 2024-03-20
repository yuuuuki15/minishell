/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:38:24 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 15:38:44 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check content of a redirect
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
