/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:34:14 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/01 16:09:40 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_execcmd *cmd)
{
	if (!cmd)
	ft_add_env(ft_strdup("PWD"), ft_strdup(cmd->argv[1]));
}
