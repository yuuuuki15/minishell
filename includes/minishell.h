/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:40:07 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/02 17:29:39 by ykawakit         ###   ########.fr       */
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
# include <signal.h>

# define PROMPT "minishell> "

// types of tokens
# define RIN		1 // > redirect input
# define PIP	3 // | pipe
# define ROUT 	2 // < redirect output, overwrite
# define AND 	4 // & background
# define DOL 	5 // $ env
# define BS 	6 // \ backslash
# define SQ 	8 // ' single quotes
# define DQ 	9 // " double quotes, expand env var
# define ROUTA 	10 // >> redirect ouput append
# define RHERE 	11 // << redirect input to heredoc

// types of cmds
# define EXEC	1
# define REDIR	2
# define PIPE	3
# define BACK	4

// configuration
# define PATH_MAX 1000

extern char	**environ;

typedef struct s_tok
{
	int		tok;
	int		s_loc;
	int		len;
	int		size;
	int		cut;
	char	*str;
	char	*quote;
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
	int		exit_status;
	t_env	*env;
}			t_shell;

extern t_shell	*g_shell;

void	ft_init_env_path(void);
void	ft_signal_manager(void);
void	ft_init_env(char **env);
int		ft_add_env(char *key, char *value);
t_env	*ft_get_env(char *name);
void	ft_clean_env(void);
void	ft_show_env(void);
void	ft_unset_env(char *key);
int		ft_is_valid_identifier(char *str);

// utils
void	ft_free_tab(char **array);
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);

// parsing utiles
int		ft_strisspace(char *line);
int		ft_issym(char c);
int		ft_istok(char c);
int		ft_isspace(char c);
int		ft_isredir(char c);
int		ft_tofile(int tok);
char	*ft_delstr(char const *s, unsigned int start, unsigned int end);
int		balance_quotes(char *str);

// parsing
int		get_data(void);
void	get_token(t_tok *tok, char *str);
t_cmd	*lexer(char *str);
int		*parse_quotes(char *str);

// cmd tree
t_cmd	*make_execcmd(void);
t_cmd	*make_backcmd(t_cmd *subcmd);
t_cmd	*make_pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*make_redircmd(t_cmd *subcmd, char *file, int mode);

// builltin
int		ft_is_builtin(t_execcmd *cmd);
int		ft_builtin_manager(t_execcmd *cmd);
int		echo(t_execcmd *cmd);
int		cd(t_execcmd *cmd);
int		env(t_execcmd *cmd);
int		export(t_execcmd *cmd);
int		unset(t_execcmd *cmd);

// exec
void	ft_exec(t_execcmd *cmd, char **env);
void	run_exec(t_cmd *cmd, char **env);
void	manage_redir(t_cmd *cmd, char **env);
void	manage_redir2(t_cmd *cmd);
void	manage_pipe(t_cmd *cmd, char **env);
void	manage_back(t_cmd *cmd, char **env);
void	run_exec(t_cmd *cmd, char **env);
int		fork_child(void);

// signals
void	set_signals(void);

// debug
void	print_tree(t_cmd *cmd);
void	ft_print_line(char *line);
void	printcmd(t_cmd *cmd);

#endif
