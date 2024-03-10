/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:27:13 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/10 19:28:42 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param cmd The command structure containing the env command.
 * @return exit status
 *
 * print PWD from environment
 */
int	ft_pwd(t_execcmd *cmd, t_shell *shell)
{
	t_env	*env;

	(void)cmd;
	env = ft_get_env("PWD", shell);
	if (env == NULL)
	{
		ft_putendl_fd(ERR_NO_PWD, STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd(env->value, STDOUT_FILENO);
	return (0);
}
