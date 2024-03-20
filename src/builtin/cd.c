/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:24:44 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/20 22:24:51 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Updates environment variables for current and old working directories.
 * @param old_pwd char*: Previous working directory.
 * @param pwd char*: Current working directory.
 * @param shell t_shell*: Shell instance.
 * @return int: Always returns 0.
 */
static int	ft_update_environment(char *old_pwd, char *pwd, t_shell *shell)
{
	ft_add_env("OLDPWD", ft_strdup(old_pwd), shell);
	ft_add_env("PWD", ft_strdup(pwd), shell);
	return (0);
}

/**
 * Changes current working directory and updates environment variables.
 * @param path char*: Path to change to.
 * @param shell t_shell*: Shell instance.
 * @return int: 0 on success, 1 on failure.
 * Error cases: Fails if current working directory cannot be retrieved,
 * if changing to new directory fails, or if updating environment fails.
 */
static int	ft_change_directory(char *path, t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];

	if (getcwd(old_cwd, PATH_MAX) == NULL)
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd(ERR_NO_SUCH_FILE_OR_DIRECTORY, STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
		return (1);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (ft_update_environment(old_cwd, cwd, shell) != 0)
		return (1);
	return (0);
}

/**
 * Handles changing to the home directory.
 * @param shell t_shell*: Shell instance.
 * @return int: 0 on success, 1 if HOME environment variable is not set.
 */
static int	ft_handle_home_directory(t_shell *shell)
{
	t_env	*path;

	path = ft_get_env("HOME", shell);
	if (!path)
	{
		ft_putendl_fd(ERR_HOME_NOT_FOUND, STDERR_FILENO);
		return (1);
	}
	return (ft_change_directory(path->value, shell));
}

/**
 * Handles changing to the previous working directory.
 * @param shell t_shell*: Shell instance.
 * @return int: 0 on success, 1 if OLDPWD environment variable is not set.
 */
static int	ft_handle_oldpwd(t_shell *shell)
{
	t_env	*path;

	path = ft_get_env("OLDPWD", shell);
	if (!path)
	{
		ft_putendl_fd(ERR_OLD_PATH_NOT_FOUND, STDERR_FILENO);
		return (1);
	}
	return (ft_change_directory(path->value, shell));
}

/**
 * Main function for cd command. Changes current working directory.
 * @param cmd t_execcmd*: Command structure with arguments passed to cd.
 * @param shell t_shell*: Shell instance.
 * @return int: 0 on success, 1 on failure.
 * Error cases: Fails if too many arguments are provided, if HOME or OLDPWD
 * environment variables are not set, or if changing directory fails.
 */
int	ft_cd(t_execcmd *cmd, t_shell *shell)
{
	if (cmd->argv[2] != NULL)
	{
		ft_putendl_fd(ERR_CD_TOO_MANY_ARGUMENT, STDERR_FILENO);
		return (1);
	}
	if (cmd->argv[1] == NULL)
		return (ft_handle_home_directory(shell));
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
		return (ft_handle_oldpwd(shell));
	else
		return (ft_change_directory(cmd->argv[1], shell));
}
