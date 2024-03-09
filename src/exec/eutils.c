/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:16:39 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/09 17:44:58 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creates a child process using fork and checks for errors.
 * @return The PID of the child process, or exits if fork fails.
 */
int	fork_child(t_shell *g_shell)
{
	g_shell->pid = fork();
	if (g_shell->pid == -1)
	{
		ft_putstr_fd(ERR_FORK, STDERR_FILENO);
		exit(1);
	}
	return (g_shell->pid);
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
char	*ft_get_path(char *cmd, t_shell *g_shell)
{
	char	**env_path;
	char	*full_path;

	env_path = NULL;
	if (ft_get_env("PATH", g_shell))
		env_path = ft_split(ft_get_env("PATH", g_shell)->value, ':');
	if (env_path == NULL)
		exit(1);
	full_path = validate_path(env_path, cmd);
	ft_free_tab(env_path);
	return (full_path);
}

/**
 * Resets the file descriptors for standard input and output to their defaults.
 */
void	reset_descriptors(t_shell *g_shell)
{
	if (g_shell->in_fd != STDIN_FILENO)
	{
		if (!g_shell->is_inside_pipe)
			close(g_shell->in_fd);
		close(STDIN_FILENO);
		dup2(g_shell->stdin, STDIN_FILENO);
	}
	if (g_shell->out_fd != STDOUT_FILENO)
	{
		if (!g_shell->is_inside_pipe)
			close(g_shell->out_fd);
		close(STDOUT_FILENO);
		dup2(g_shell->stdout, STDOUT_FILENO);
	}
}

/**
 * Duplicates the file descriptors for input and output
 * if they have been redirected.
 */
void	dup_descriptors(t_shell *g_shell)
{
	if (g_shell->in_fd != STDIN_FILENO)
	{
		dup2(g_shell->in_fd, STDIN_FILENO);
		close(g_shell->in_fd);
	}
	if (g_shell->out_fd != STDOUT_FILENO)
	{
		dup2(g_shell->out_fd, STDOUT_FILENO);
	}
}
