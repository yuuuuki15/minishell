/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:37:21 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/28 17:47:58 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	shell;

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
	int		do_exe;
	t_cmd	*cmd;

	ft_init_env_path(&shell);
	ft_add_env("TEST", "HOGE");
	ft_clean_env();
	ft_printf("test: %s\n", ft_get_env("TEST"));
	while (1)
	{
		do_exe = get_data(&shell);
		if (do_exe)
		{
			cmd = lexer(shell.user_input);
			run_exec(cmd, &shell);
		}
	}
	return (0);
}
