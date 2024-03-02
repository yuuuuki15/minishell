/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:34:14 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 16:09:02 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_update_environment(char *oldpwd, char *newpwd)
{
	ft_add_env("OLDPWD", ft_strdup(oldpwd));
	ft_add_env("PWD", ft_strdup(newpwd));
}

static void ft_change_directory(char *path)
{
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];

	if (getcwd(old_cwd, PATH_MAX) == NULL)
		return ;
	if (chdir(path) == -1)
	{
		ft_putstr_fd(ERR_NO_SUCH_FILE_OR_DIRECTORY, STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
		return;
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	ft_update_environment(old_cwd, cwd);
}

static void ft_handle_home_directory(void)
{
	t_env	*path;

	path = ft_get_env("HOME");
	if (!path)
	{
		ft_putendl_fd(ERR_HOME_NOT_FOUND, STDERR_FILENO);
		return;
	}
	ft_change_directory(path->value);
}

static void ft_handle_oldpwd(void)
{
	t_env	*path;

	path = ft_get_env("OLDPWD");
	if (!path)
	{
		ft_putendl_fd(ERR_OLD_PATH_NOT_FOUND, STDERR_FILENO);
		return;
	}
	ft_change_directory(path->value);
}

static void ft_handle_custom_path(t_execcmd *cmd)
{
	if (cmd->argv[2] != NULL)
	{
		ft_putstr_fd(ERR_STRING_NOT_IN_PWD, STDERR_FILENO);
		ft_putendl_fd(cmd->argv[1], STDERR_FILENO);
		return;
	}
	ft_change_directory(cmd->argv[1]);
}

void cd(t_execcmd *cmd)
{
	if (cmd->argv[1] == NULL)
		ft_handle_home_directory();
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
		ft_handle_oldpwd();
	else
		ft_handle_custom_path(cmd);
}
