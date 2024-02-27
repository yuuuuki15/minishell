/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/27 18:35:09 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param t_shell* shell
 *
 * This function will initialize environment path of the system.
 * And put them in shell->env_path.
*/
void	ft_init_env_path(t_shell *shell)
{
	ft_add_env("PATH", getenv("PATH"));
	shell->user_input = NULL;
}

/**
 * @param t_shell shell
 * @param char* cmd
 *
 * @return char* fullpath
 *
 * This function takes user input and try to execute with every
 * environment path. Return fullpath on success.
*/
char	*ft_get_path(t_shell *shell, char *cmd)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = -1;
	while (shell->env_path[++i])
	{
		temp = ft_strjoin(shell->env_path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

/**
 * @param t_shell *shell
 * @param t_execcmd *cmd
 *
 * This function takes executive command provided by parser,
 * checks path using env info from shell then
 * executes command. Print error message when error occurs.
 * Command array is freed after execution.
*/
void	ft_exec(t_execcmd *cmd, t_shell *shell)
{
	char	*pathname;
	int		res;

	if (ft_is_builtin(cmd))
	{
		ft_builtin_manager(cmd, shell);
		exit(0);
	}
	pathname = ft_get_path(shell, cmd->argv[0]);
	res = execve(pathname, cmd->argv, NULL);
	if (res < 0)
	{
		if (pathname != NULL)
			free(pathname);
		ft_putstr_fd(ERR_COMMAND_NOT_FOUND, STDERR_FILENO);
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
		ft_free_tab(cmd->argv);
		free (cmd);
		exit(errno);
	}
}
