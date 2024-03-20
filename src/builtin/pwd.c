/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:27:13 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 22:30:45 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints the current working directory.
 *
 * @param cmd t_execcmd*: The command structure containing the pwd command.
 * @param shell t_shell*: The shell instance to access environment variables.
 * @return int: Returns 0 on success, 1 on error.
 *
 * Error cases: Returns 1 if an unsupported option is provided or if the PWD
 * environment variable is not set.
 */
int	ft_pwd(t_execcmd *cmd, t_shell *shell)
{
	t_env	*env;

	env = ft_get_env("PWD", shell);
	if (cmd->argv[1] != NULL && cmd->argv[1][0] == '-')
	{
		ft_putendl_fd(ERR_OPTION_NOT_SUPPORTED, STDERR_FILENO);
		return (1);
	}
	if (env == NULL)
	{
		ft_putendl_fd(ERR_NO_PWD, STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd(env->value, STDOUT_FILENO);
	return (0);
}
