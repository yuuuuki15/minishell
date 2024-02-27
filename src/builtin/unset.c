/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:36 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/27 14:59:36 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_execcmd *cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;
	// check the flag -n for not printing newline at the end
	// print everything with separator ' '(space) when there's multiple arg
	ft_printf("unset has been pressed\n");
}
