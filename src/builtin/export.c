/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:24 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/29 15:44:12 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_execcmd *cmd, t_shell *shell)
{
	int	i;

	(void)cmd;
	(void)shell;
	i = 0;
	while (cmd->argv[++i])
		ft_add_env(ft_get_key(cmd->argv[i]), ft_get_value(cmd->argv[i]));
}
