/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:16:39 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/27 10:08:29 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creates a child process and checks for errors.
 * @param shell t_shell*: The shell instance.
 * @return int: The PID of the child process, or exits if fork fails.
 * @error Exits with 1 if fork fails.
 */
int	fork_child(t_shell *shell)
{
	shell->pid = fork();
	if (shell->pid == -1)
	{
		ft_putstr_fd(ERR_FORK, STDERR_FILENO);
		clean_exit(shell);
		exit(1);
	}
	return (shell->pid);
}

/**
 * Validates the command path against the environment PATH variable.
 * @param env_path char**: The split PATH environment variable.
 * @param cmd char*: The command to validate.
 * @return char*: The full path to the command
 * if found and executable, otherwise NULL.
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
 * @param cmd char*: The command to find the path for.
 * @param shell t_shell*: The shell instance.
 * @return char*: The full path to the command if found, otherwise exits.
 * @error Exits with 126 if cmd is a directory or not executable.
 */
char	*ft_get_path(char *cmd, t_shell *shell)
{
	char		**env_path;
	char		*full_path;
	struct stat	path_stat;

	env_path = NULL;
	if (stat(cmd, &path_stat) != -1)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putendl_fd("Is a directory", STDERR_FILENO);
			clean_exit(shell);
			exit(126);
		}
	}
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (ft_get_env("PATH", shell))
		env_path = ft_split(ft_get_env("PATH", shell)->value, ':');
	else if (shell->env_i_flag == 1)
		env_path = ft_split("/usr/bin/", ':');
	if (env_path == NULL)
		return (ft_strdup(" "));
	full_path = validate_path(env_path, cmd);
	ft_free_tab(env_path);
	return (full_path);
}

/**
 * Duplicates the file descriptors for input and output if redirected.
 * @param shell t_shell*: The shell instance.
 */
void	dup_descriptors(t_shell *shell)
{
	if (shell->in_fd >= 0 && shell->in_fd != STDIN_FILENO)
	{
		dup2(shell->in_fd, STDIN_FILENO);
		close(shell->in_fd);
	}
	if (shell->out_fd >= 0 && shell->out_fd != STDOUT_FILENO)
	{
		dup2(shell->out_fd, STDOUT_FILENO);
		close(shell->out_fd);
	}
}
