/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:40:07 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/13 19:06:52 by ykawakit         ###   ########.fr       */
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

// types of tokens
# define RIN	1 // < redirect input
# define ROUT 	2 // > redirect output, overwrite
# define PIP	3 // | pipe
# define AND 	4 // & background
# define SQ 	8 // ' single quotes
# define DQ 	9 // " double quotes, expand env var
# define ROUTA 	10 // >> redirect ouput append
# define RHERE 	11 // << redirect input to heredoc
# define DOL 	12 // $ env
# define OP		13 // open parenthesis
# define CP		14 // close parenthesis
# define FERR	15 // file read error

// types of cmds
# define EXEC	1
# define REDIR	2
# define PIPE	3
# define BACK	4 // & run in background, not supported
# define IFTHEN	5 // && if cmd 1 executes then also execute cmd 2
# define IFOR	6 // || if cmd 1 does not execute, then execute cmd 2

# define STDIN	0
# define STOUT	1
# define STERR	2

// configuration
# define PATH_MAX 1000

//extern char	**environ;

typedef struct s_tok
{
	int		tok;
	int		s_loc;
	int		len;
	int		size;
	int		cut;
	char	*str;
}	t_tok;

typedef struct s_cmd
{
	int		type;
	int		in_fd;
	int		out_fd;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	**argv;
	int		in_fd;
	int		out_fd;
}	t_execcmd;

typedef struct s_backcmd
{
	int		type;
	t_cmd	*cmd;
}	t_backcmd;

typedef struct s_listcmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_listcmd;

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
	char	*user_input;
	int		fd[2];
	int		in_fd;
	int		out_fd;
	int		stdin;
	int		stdout;
	int		pid;
	int		exit_status;
	int		is_inside_pipe;
	int		exit_prog;
	t_cmd	*head_cmd;
	t_env	*env;
}			t_shell;

void	ft_signal_manager(int option);
int		ft_init_env(char **env, t_shell *shell);
int		ft_add_env(char *key, char *value, t_shell *shell);
t_env	*ft_get_env(char *name, t_shell *shell);
void	ft_clean_env(t_shell *shell);
void	ft_show_env(t_shell *shell);
void	ft_unset_env(char *key, t_shell *shell);
int		ft_is_valid_identifier(char *str);
void	exit_shell(t_shell *shell);
int		ft_set_pwd(t_shell *shell);

// utils
void	ft_free_tab(char **array);
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);

// parsing utiles
int		ft_strisspace(char *line);
int		ft_issym(char c);
int		ft_istok(char c);
int		ft_isspace(char c);
int		ft_isallowed(char c);
int		ft_tofile(int tok);
char	*ft_delstr(char const *s, unsigned int start, unsigned int end);

// parsing
int		get_data(t_shell *shell);
void	get_token(t_tok *tok, char *str);
t_cmd	*lexer(char *str, t_shell *shell);
char	**p_spliter(char *s);
int		is_pipe(char *str, t_tok *tok);
t_cmd	*parse_pipe(char *str, t_tok *tok, t_shell *shell);
t_cmd	*parsecmd(char *str, t_tok *tok, t_shell *shell);
void	get_file_name(t_tok *tok, int i, int size, char *str);
void	get_redir_token(t_tok *tok, int i, char *str);

// bonus parsing
t_cmd	*parse_ifthen(char *str, t_tok *tok, t_shell *shell);
int		is_ifthen(char *str, t_tok *tok, int *q_check, int *p_check);
int		is_ifor(char *str, t_tok *tok, int *q_check, int *p_check);
int		has_first_level(char *str, t_tok *tok);
int		balance_para(char *str, int *in_quotes);
void	zero_array(int *in_quotes, int len);
int		*parse_para(char *str);
int		check_tree(t_cmd *cmd, t_shell *shell);
int		balance_pandq(char *str);
t_cmd	*parse_paren(char *str, t_shell *shell);

// variables
char	*expand_var(char *str, t_shell *shell);

// quotes
int		*parse_quotes(char *str);
int		balance_quotes(char *str);
char	*remove_quotes(char *str);
void	clean_quotes(char **tab, t_shell *shell);

// cmd tree
t_cmd	*make_execcmd(void);
t_cmd	*make_backcmd(t_cmd *subcmd);
t_cmd	*make_listcmd(t_cmd *left, t_cmd *right, int type);
t_cmd	*make_redircmd(t_cmd *subcmd, char *file, int mode);

// builltin
int		ft_is_builtin(t_execcmd *cmd);
int		ft_builtin_manager(t_execcmd *cmd, t_shell *shell);
int		ft_echo(t_execcmd *cmd);
int		ft_cd(t_execcmd *cmd, t_shell *shell);
int		ft_env(t_execcmd *cmd, t_shell *shell);
int		ft_export(t_execcmd *cmd, t_shell *shell);
int		ft_unset(t_execcmd *cmd, t_shell *shell);
int		ft_pwd(t_execcmd *cmd, t_shell *shell);
int		ft_exit(t_execcmd *cmd, t_shell *shell);

// exec
void	ft_exec(t_execcmd *cmd, char **env, t_shell *shell);
void	run_exec(t_cmd *cmd, char **env, t_shell *shell);
void	manage_redir(t_cmd *cmd, char **env, t_shell *shell);
void	manage_pipe(t_cmd *cmd, char **env, t_shell *shell);
void	manage_back(t_cmd *cmd, char **env, t_shell *shell);
void	manage_andor(t_cmd *cmd, char **env, t_shell *shell);
int		fork_child(t_shell *shell);
char	*ft_get_path(char *cmd, t_shell *shell);
void	reset_descriptors(t_shell *shell);
void	dup_descriptors(t_shell *shell);

// signals
void	set_signals(void);

// debug
void	print_tree(t_cmd *cmd);
void	ft_print_line(char *line);
void	printcmd(t_cmd *cmd);

// clean
void	clean_tree(t_cmd *cmd);
void	clean_exit(t_shell *shell);

// error handling
void	ft_error(char *error_message);

#endif
