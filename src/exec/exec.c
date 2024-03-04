/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/04 09:16:10 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function will initialize environment path of the system.
 * And put them in g_shell->env_path.
*/
void	ft_init_env_path(void)
{
	ft_add_env("PATH", getenv("PATH"));
	g_shell->user_input = NULL;
}

/**
 * @param char* cmd
 *
 * @return char* fullpath
 *
 * This function takes user input and try to execute with every
 * environment path. Return fullpath on success.
*/
char	*ft_get_path(char *cmd)
{
	char	*full_path;
	char	*temp;
	char	**env_path;
	int		i;

	(void)g_shell;
	i = -1;
	env_path = NULL;
	if (ft_get_env("PATH"))
		env_path = ft_split(ft_get_env("PATH")->value, ':');
	if (env_path == NULL)
		exit(1);
	while (env_path[++i])
	{
		temp = ft_strjoin(env_path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_tab(env_path);
			return (full_path);
		}
		free(full_path);
	}
	ft_free_tab(env_path);
	return (NULL);
}

/**
 * @param t_execcmd *cmd
 *
 * This function takes executive command provided by parser,
 * checks path using env info from shell then
 * executes command. Print error message when error occurs.
*/
void	ft_exec(t_execcmd *cmd, char **env)
{
	char	*pathname;
	int		res;

	pathname = ft_get_path(cmd->argv[0]);
	res = execve(pathname, cmd->argv, env);
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

// directs the execution of the cammand tree
// BACK is managed and resubmited to run_exec prior to fork
// REDIR is managed after fork
// PIPE is in progress
void	run_exec(t_cmd *cmd, char **env)
{
	t_execcmd	*ecmd;

	ft_printf("Executing type: %d\n", cmd->type);
	if (cmd->type == EXEC || cmd->type == REDIR)
	{
		if (cmd->type == EXEC)
		{
			ecmd = (t_execcmd *)cmd;
			if (ft_is_builtin(ecmd))
			{
				g_shell->exit_status = ft_builtin_manager((t_execcmd *)cmd);
				return ;
			}
		}
		g_shell->pid = fork_child();
		if (g_shell->pid == 0)
		{
			if (cmd->type == REDIR)
				manage_redir2(cmd);
			ft_exec(ecmd, env);
		}
		else
			wait(NULL);
	}
	if (cmd->type == BACK)
		manage_back(cmd, env);
	if (cmd->type == PIPE)
	{
		ft_printf("Piping is not currently working.\n");
		manage_pipe(cmd, env);
	}
}
