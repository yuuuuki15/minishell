/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:40:07 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/20 19:48:51 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include "message.h"
#include <unistd.h>
#include <errno.h>

typedef struct s_shell
{
	char	**env_path;
	char	*user_input;
	int		fd[2];
	int		pid;
}			t_shell;

void	ft_init_env_path(t_shell *shell);
void	ft_exec(t_shell shell);
void	ft_free_tab(char **array);

#endif
