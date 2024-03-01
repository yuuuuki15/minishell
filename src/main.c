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
		shell->pid = fork();
		if (shell->pid == -1)
		{
			ft_putstr_fd(ERR_FORK, STDERR_FILENO);
			exit(1);
		}
		if (shell->pid == 0)
			ft_exec(ecmd);
		else
			wait(NULL);
	}
	if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		run_exec(bcmd->cmd);
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
			run_exec(cmd);
		}
	}
	return (0);
}
