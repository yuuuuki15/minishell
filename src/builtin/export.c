/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:24 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/28 18:42:16 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_execcmd *cmd, t_shell *shell)
{
	// int	i;

	(void)cmd;
	(void)shell;
	// when it's hoge=hoge=hoge
	// key   -> hoge
	// value -> hoge=hoge
	// so key takes first part until = appears.
	// value is the rest.
	// i = 0;
	// while (cmd->argv[++i])
	// {

	// }
	ft_printf("export has been pressed\n");
}
