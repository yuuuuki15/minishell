/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:40:07 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/01 17:53:24 by ykawakit         ###   ########.fr       */
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
# include <fcntl.h>

# define PROMPT "minishell> "

# define RINPUT		1 // > redirect input
# define PIP	3 // | pipe
# define LT 	2 // < redirect output, overwrite
# define AND 	4 // & background
# define DOL 	5 // $ env
# define BS 	6 // \ backslash
# define SQ 	8 // ' single quotes
# define DQ 	9 // " double quotes, expend env var
# define DGT 	10 // >> redirect ouput append
# define DLT 	11 // << redirect input to heredoc

// types of cmds
# define EXEC	1
# define REDIR	2
# define PIPE	3
# define BACK	4

extern char	**environ;

typedef struct s_tok
{
	int		tok;
	int		s_loc;
	int		len;
	char	*str;
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

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
}	t_redircmd;

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
void	ft_exec(t_execcmd *cmd, char **env);

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
void	get_token(t_tok *tok, char *str);
t_cmd	*lexer(char *str);

t_cmd	*make_execcmd(void);
t_cmd	*make_backcmd(t_cmd *subcmd);
t_cmd   *make_pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*make_redircmd(t_cmd *subcmd, char *file, int mode, int fd);

char	*ft_delstr(char const *s, unsigned int start, size_t len);

// builltin
int		ft_is_builtin(t_execcmd *cmd);
void	ft_builtin_manager(t_execcmd *cmd, t_shell *shell);
void	echo(t_execcmd *cmd);
void	cd(t_execcmd *cmd, t_shell *shell);
void	env(t_execcmd *cmd, t_shell *shell);
void	export(t_execcmd *cmd, t_shell *shell);
void	unset(t_execcmd *cmd, t_shell *shell);

char	*ft_delstr(char const *s, unsigned int start, size_t len);
void	run_exec(t_cmd *cmd, char **env);


#endif
