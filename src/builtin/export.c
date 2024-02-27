/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:24 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/27 14:59:31 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_execcmd *cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;
	// check the flag -n for not printing newline at the end
	// print everything with separator ' '(space) when there's multiple arg
	ft_printf("export has been pressed\n");
}
