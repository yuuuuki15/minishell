/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:34:14 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/29 15:39:37 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_execcmd *cmd, t_shell *shell)
{
	(void)cmd;
	(void)shell;
	ft_add_env(ft_strdup("PWD"), ft_strdup(cmd->argv[1]));
}
