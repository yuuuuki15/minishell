/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:16:39 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/10 19:05:56 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creates a child process using fork and checks for errors.
 * @return The PID of the child process, or exits if fork fails.
 */
int	fork_child(t_shell *shell)
{
	shell->pid = fork();
	if (shell->pid == -1)
	{
		ft_putstr_fd(ERR_FORK, STDERR_FILENO);
		exit(1);
	}
	return (shell->pid);
}

/**
 * Validates the command path against the environment PATH variable.
 * @param env_path The split PATH environment variable.
 * @param cmd The command to validate.
 * @return The full path to the command if found and executable, otherwise NULL.
 */
static char	*validate_path(char **env_path, char *cmd)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = -1;
	while (env_path[++i])
	{
		temp = ft_strjoin(env_path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

/**
 * Retrieves the full path of a command from the PATH environment variable.
 * @param cmd The command to find the path for.
 * @return The full path to the command if found, otherwise exits.
 */
char	*ft_get_path(char *cmd, t_shell *shell)
{
	char	**env_path;
	char	*full_path;

	env_path = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (ft_get_env("PATH", shell))
		env_path = ft_split(ft_get_env("PATH", shell)->value, ':');
	if (env_path == NULL)
		exit(1);
	full_path = validate_path(env_path, cmd);
	ft_free_tab(env_path);
	return (full_path);
}

/**
 * Resets the file descriptors for standard input and output to their defaults.
 */
void	reset_descriptors(t_shell *shell)
{
	if (shell->in_fd != STDIN_FILENO)
	{
		if (!shell->is_inside_pipe)
			close(shell->in_fd);
		close(STDIN_FILENO);
		dup2(shell->stdin, STDIN_FILENO);
	}
	if (shell->out_fd != STDOUT_FILENO)
	{
		if (!shell->is_inside_pipe)
			close(shell->out_fd);
		close(STDOUT_FILENO);
		dup2(shell->stdout, STDOUT_FILENO);
	}
}

/**
 * Duplicates the file descriptors for input and output
 * if they have been redirected.
 */
void	dup_descriptors(t_shell *shell)
{
	if (shell->in_fd != STDIN_FILENO)
	{
		dup2(shell->in_fd, STDIN_FILENO);
		close(shell->in_fd);
	}
	if (shell->out_fd != STDOUT_FILENO)
	{
		dup2(shell->out_fd, STDOUT_FILENO);
		close(shell->out_fd);
	}
}
