/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eutils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:38:24 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/25 14:46:23 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks the content of a file for redirection purposes.
 * @param file char*: The file name to check.
 * @param shell t_shell*: The shell instance for updating exit status.
 * @return int: Returns 1 if the file content is invalid, otherwise 0.
 * @error If the file content is empty or only spaces, prints an error message
 * and sets the shell's exit status to 2.
 */
int	check_file(char *file, t_shell *shell)
{
	char		*temp;

	temp = ft_strtrim(file, " ");
	if (ft_strcmp(temp, "") == 0)
	{
		ft_putendl_fd("unaccepted token", STDERR_FILENO);
		shell->exit_status = 2;
		free (temp);
		return (1);
	}
	free (temp);
	return (0);
}

static int	count_exported_env(t_shell *shell)
{
	t_env	*env_list;
	int		count;

	env_list = shell->env;
	count = 0;
	while (env_list)
	{
		if (env_list->exported)
			count++;
		env_list = env_list->next;
	}
	return (count);
}

static char	*create_env_str(char *key, char *value)
{
	char	*env_str;
	int		len;

	len = strlen(key) + strlen(value) + 2;
	env_str = (char *)malloc(sizeof(char) * len);
	if (!env_str)
		return (NULL);
	strcpy(env_str, key);
	strcat(env_str, "=");
	strcat(env_str, value);
	return (env_str);
}

static void	free_env_array(char **env_array, int i)
{
	while (i > 0)
		free(env_array[--i]);
	free(env_array);
}

char	**env_to_char_array(t_shell *shell)
{
	char	**env_array;
	int		env_count;
	int		i;
	t_env	*env_list;

	env_count = count_exported_env(shell);
	env_array = (char **)malloc(sizeof(char *) * (env_count + 1));
	if (!env_array)
		return (NULL);
	env_list = shell->env;
	i = -1;
	while (env_list && ++i < env_count)
	{
		if (env_list->exported == 0)
			continue ;
		env_array[i] = create_env_str(env_list->key, env_list->value);
		if (!env_array[i])
		{
			free_env_array(env_array, i);
			return (NULL);
		}
		env_list = env_list->next;
	}
	env_array[env_count] = NULL;
	return (env_array);
}
