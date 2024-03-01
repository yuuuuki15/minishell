/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:40:07 by ykawakit          #+#    #+#             */
/*   Updated: 2024/02/29 15:51:15 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "message.h"
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define PROMPT "minishell> "

# define GT 1 //greater than
# define PIP 3 //pipe
# define LT 2 // less than
# define AND 4 // and
# define SC 5 // single...
# define OP 6 //
# define CP 7
# define SQ 8
# define DQ 9
# define DGT 10
# define DLT 11

// types of cmds
# define EXEC	1
# define REDIR	2
# define PIPE	3
# define BACK	4

typedef struct s_tok
{
	int	tok;
	int	i;
}	t_tok;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	**argv;
}	t_execcmd;

typedef struct s_backcmd
{
	int		type;
	t_cmd	*cmd;
}	t_backcmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	char	**env_path;
	char	*user_input;
	int		fd[2];
	int		pid;
	t_env	*env;
}			t_shell;

extern	t_shell *shell;

void	ft_init_env_path(t_shell *shell);
void	ft_init_env(char **env);
int		ft_add_env(char *key, char *value);
t_env	*ft_get_env(char *name);
void	ft_clean_env(void);
void	ft_show_env(void);
void	ft_unset_env(char *key);
void	ft_exec(t_execcmd *cmd);

// utils
void	ft_free_tab(char **array);
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);

// parsing
void	ft_print_line(char *line);
int		handle_space(void);
int		ft_strisspace(char *line);
int		ft_issym(char c);
int		ft_isspace(char c);

int		get_data(t_shell *shell);
void		get_token(t_tok *tok, char *st, char *et);
t_cmd	*lexer(char *str);

t_cmd	*make_execcmd(void);
t_cmd	*make_backcmd(void);
t_cmd   *make_pipecmd(t_cmd *left, t_cmd *right);

// builltin
int		ft_is_builtin(t_execcmd *cmd);
void	ft_builtin_manager(t_execcmd *cmd, t_shell *shell);
void	echo(t_execcmd *cmd);
void	cd(t_execcmd *cmd, t_shell *shell);
void	env(t_execcmd *cmd, t_shell *shell);
void	export(t_execcmd *cmd, t_shell *shell);
void	unset(t_execcmd *cmd, t_shell *shell);

#endif
