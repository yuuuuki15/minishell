#include "minishell.h"

void	reset_prompt(void)
{
	//rl_on_new_line();
	free (shell->user_input);
	shell->user_input = ft_strdup(" ");
	//rl_redisplay();
}

void	sig_test(int signum)
{
	if (signum == SIGINT) // ctrl-c
	{
		//free (shell->user_input);
		//shell->user_input = NULL;
		//rl_on_new_line();
		// this is essentially canceling everything so need to kill processes
		// and wipe everything clean
		ft_printf("\nminishell> ");
		shell->sig = 0;
		reset_prompt();
	}
	if (signum == SIGQUIT) // ctrl-backslash
	{
		ft_printf("");
		shell->sig = 1;
		//reset_prompt();
		//rl_on_new_line();
		// I am not certain what behavior is expected here
		// currently does nothing but returns extra newline after enter
	//	return ;
	}
}

void	set_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = &sig_test;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}