/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/26 08:54:22 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exec(t_cmd *cmd, t_shell *shell)
{
	t_backcmd	*bcmd;
	t_execcmd	*ecmd;

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
			ft_exec(ecmd, shell);
		else
			wait(NULL);
	}
	if (cmd->type == BACK)
	{
		bcmd = (t_backcmd *)cmd;
		run_exec(bcmd->cmd, shell);
	}
}

int	main(void)
{
	t_shell	shell;
	int		do_exe;
	t_cmd	*cmd;

	ft_init_env_path(&shell);
	while (1)
	{
		do_exe = get_data(&shell);
		if (do_exe)
		{
			cmd = lexer(shell.user_input);
			run_exec(cmd, &shell);
		}
	}
	rl_clear_history();
	return (0);
}
