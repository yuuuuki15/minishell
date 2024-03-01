/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/29 15:39:08 by ykawakit         ###   ########.fr       */
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

void	manage_pipe(t_cmd *cmd, char **env)
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
		run_exec(pcmd->left, env);
	}
	if (fork_child() == 0)
	{
		close(0);
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		//close(p[1]);
		run_exec(pcmd->right, env);
	}
	close(p[1]);
	close(p[0]);
	wait(NULL);
	wait(NULL);
	exit(0);
}

void	manage_redir(t_cmd *cmd, char **env)
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
	run_exec(rcmd->cmd, env);
}

void	run_exec(t_cmd *cmd, char **env)
{
	t_backcmd	*bcmd;
	t_execcmd	*ecmd;
	
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		shell->pid = fork_child();
		if (shell->pid == 0)
			ft_exec(ecmd, env);
		else
			wait(NULL);
	}
	if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		ft_printf("Background jobs not supported. Running command in foreground.\n");
		run_exec(bcmd->cmd, env);
	}
	if (cmd->type == PIPE)
	{
		ft_printf("Piping is not currently working.\n");
		manage_pipe(cmd, env);
	}
	if (cmd->type == REDIR)
	{
		ft_printf("Sending cmd to redirect manager\n");
		manage_redir(cmd, env);
	}
}

void	sig_test(int signum)
{
	if (signum == SIGINT) // ctrl-c
	{
		ft_printf("\nminishell> ");
	}
	if (signum == SIGQUIT) // ctrl-backslash
	{
		ft_printf("");
	}
}

int	main(int ac, char **av, char **env)
{
	int		do_exe;
	t_cmd	*cmd;
	struct sigaction sa;

	sa.sa_handler = &sig_test;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	(void)ac;
	(void)av;
	// ft_init_env_path(&shell);
	// init every environment variable.
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (1);
	ft_init_env(env);
	while (1)
	{
		do_exe = get_data(shell);
		if (do_exe)
		{
			cmd = lexer(shell->user_input);
			run_exec(cmd, env); //passing env to exeutor so that commands like clear work
		}
	}
	return (0);
}
