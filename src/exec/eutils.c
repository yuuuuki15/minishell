/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:16:39 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/04 09:16:44 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check for fork error
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
