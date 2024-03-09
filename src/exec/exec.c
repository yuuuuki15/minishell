/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:41:30 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/09 15:27:19 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param t_execcmd *cmd
 *
 * This function takes executive command provided by parser,
 * checks path using env info from shell then
 * executes command. Print error message when error occurs.
*/
void	ft_exec(t_execcmd *cmd, char **env, t_shell *g_shell)
{
	char	*pathname;
	int		res;

	pathname = ft_get_path(cmd->argv[0], g_shell);
	res = execve(pathname, cmd->argv, env);
	if (res < 0)
	{
		if (pathname != NULL)
			free(pathname);
		ft_putstr_fd(ERR_COMMAND_NOT_FOUND, STDERR_FILENO);
		g_shell->exit_status = 127;
		ft_putendl_fd(cmd->argv[0], STDERR_FILENO);
		ft_free_tab(cmd->argv);
		free (cmd);
		exit(errno);
	}
}

static void	handle_builtin(t_execcmd *ecmd, t_shell *g_shell)
{
	dup_descriptors(g_shell);
	g_shell->exit_status = ft_builtin_manager(ecmd, g_shell);
	reset_descriptors(g_shell);
}

// manage the executable part of the tree by forking
static void	manage_exec(t_cmd *cmd, char **env, t_shell *g_shell)
{
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	if (ft_is_builtin(ecmd))
	{
		handle_builtin(ecmd, g_shell);
		return ;
	}
	g_shell->pid = fork_child(g_shell);
	if (g_shell->pid == 0)
	{
		dup_descriptors(g_shell);
		ft_exec(ecmd, env, g_shell);
	}
	else
	{
		waitpid(g_shell->pid, NULL, 0);
		reset_descriptors(g_shell);
	}
}

// directs the execution of the cammand tree
void	run_exec(t_cmd *cmd, char **env, t_shell *g_shell)
{
	if (cmd->type == REDIR)
		manage_redir(cmd, env, g_shell);
	if (cmd->type == EXEC)
		manage_exec(cmd, env, g_shell);
	if (cmd->type == BACK)
		manage_back(cmd, env, g_shell);
	if (cmd->type == PIPE)
	{
		if (fork_child(g_shell) == 0)
			manage_pipe(cmd, env, g_shell);
		else
			waitpid(g_shell->pid, NULL, 0);
	}
	if (cmd->type == IFTHEN || cmd->type == IFOR)
		manage_andor(cmd, env);
}
