/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/01 15:36:32 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell;

int	fork_child(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd(ERR_FORK, STDERR_FILENO);
		exit(1);
	}
	return (pid);
}

void	manage_pipe(t_cmd *cmd)
{
	t_pipecmd	*pcmd;
	int			p[2];

	pcmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
	{
		ft_printf("Pipe error\n");
		exit(1);
	}
	if (fork_child() == 0)
	{
		//close(1);
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		run_exec(pcmd->left);
	}
	if (fork_child() == 0)
	{
		close(0);
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		//close(p[1]);
		run_exec(pcmd->right);
	}
	close(p[1]);
	close(p[0]);
	wait(NULL);
	wait(NULL);
	exit(0);
}

void	manage_redir(t_cmd *cmd)
{
	t_redircmd	*rcmd;


	rcmd = (t_redircmd *)cmd;
	close(rcmd->fd);
	rcmd->fd = open(rcmd->file, rcmd->mode);
	ft_printf("fd: %d\n", rcmd->fd);
	if (rcmd->fd < 0)
	{
		ft_printf("open file error, clean this up!\n");
		exit(1);
	}
	// for redirect input
	if (rcmd->mode == O_RDONLY)
		dup2(rcmd->fd, 0);
	free(rcmd->file);
	ft_printf("This executes but results in a seg fault\n");
	run_exec(rcmd->cmd);
}

void	run_exec(t_cmd *cmd)
{
	t_backcmd	*bcmd;
	t_execcmd	*ecmd;

	if (ft_is_builtin((t_execcmd *)cmd))
	{
		ft_builtin_manager((t_execcmd *)cmd, shell);
		return ;
	}
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		shell->pid = fork_child();
		if (shell->pid == 0)
			ft_exec(ecmd);
		else
			wait(NULL);
	}
	if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		ft_printf("Background jobs not supported. Running command in foreground.\n");
		run_exec(bcmd->cmd);
	}
	if (cmd->type == PIPE)
	{
		ft_printf("Piping is not currently working.\n");
		manage_pipe(cmd);
	}
	if (cmd->type == REDIR)
	{
		ft_printf("Sending cmd to redirect manager\n");
		manage_redir(cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	int					do_exe;
	t_cmd				*cmd;

	(void)ac;
	(void)av;
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (1);
	ft_init_env(env);
	ft_signal_manager();
	while (1)
	{
		do_exe = get_data(shell);
		if (do_exe)
		{
			cmd = lexer(shell->user_input);
			run_exec(cmd);
		}
	}
	clear_history();
	return (0);
}
