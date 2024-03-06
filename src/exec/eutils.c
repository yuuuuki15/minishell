/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:16:39 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/06 13:18:38 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_child(void)
{
	g_shell->pid = fork();
	if (g_shell->pid == -1)
	{
		ft_putstr_fd(ERR_FORK, STDERR_FILENO);
		exit(1);
	}
	return (g_shell->pid);
}
