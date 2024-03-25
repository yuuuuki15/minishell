/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:45 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/25 20:49:31 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_show_env_fd(t_shell *shell, int fd)
{
	t_env	*curr;

	if (shell->env == NULL)
		return ;
	curr = shell->env;
	while (curr != NULL)
	{
		if (curr->exported)
		{
			ft_putstr_fd(curr->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(curr->value, fd);
			ft_putstr_fd("\n", fd);
		}
		curr = curr->next;
	}
}

/**
 * Executes the env command which prints the current environment variables.
 * @param cmd t_execcmd*: The command structure containing the env command.
 * @param shell t_shell*: The shell instance containing environment variables.
 * @return int: Always returns 0 to indicate success, 1 if an unsupported option
 * or argument is provided.
 * Error cases: Returns 1 if an unsupported option or argument is provided.
 */
int	ft_env(t_execcmd *cmd, t_shell *shell, int fd)
{
	int	ret_val;

	ret_val = 0;
	if (cmd->argv[1] != NULL)
	{
		if (cmd->argv[1][0] == '-')
		{
			ft_putendl_fd(ERR_OPTION_NOT_SUPPORTED, STDERR_FILENO);
			ret_val = 1;
		}
		else
		{
			ft_putendl_fd(ERR_ARGUMENT_NOT_SUPPORTED, STDERR_FILENO);
			ret_val = 1;
		}
	}
	else
	{
		ft_show_env_fd(shell, fd);
	}
	return (ret_val);
}
