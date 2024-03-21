/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:34:01 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:50:31 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks for a variable or quotes at the start of a string.
 * @param str char*: The string to check.
 * @return int: 1 if a variable is found, 2 if quotes are found, 0 otherwise.
 */
static int	first_var_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]) == 1)
		i++;
	while (str[i] != '\0' && ft_isspace(str[i]) == 0)
	{
		if (str[i] == '$')
			return (1);
		if (str[i] == '"')
			return (2);
		i++;
	}
	return (0);
}

/**
 * Parses and stores commands in command structures within a tree.
 * @param cmd t_execcmd*: The command structure to store parsed commands.
 * @param str char*: The string containing the command to parse.
 * @param shell t_shell*: The shell environment.
 */
static void	parsexe(t_execcmd *cmd, char *str, t_shell *shell)
{
	char		*substr;

	if (first_var_check(str) == 1)
	{
		substr = expand_var(str, shell);
		if (ft_strcmp(substr, "") != 0)
			cmd->argv = p_spliter(substr);
		if (substr)
			free (substr);
	}
	else
	{
		cmd->argv = p_spliter(str);
		clean_quotes(cmd->argv, shell);
	}
}

/**
 * Expands variables and removes quotes in file names.
 * @param tok t_tok*: The token containing the file name.
 * @param shell t_shell*: The shell environment.
 */
static void	expand_file_name(t_tok *tok, t_shell *shell)
{
	char	*sub;

	sub = expand_var(tok->str, shell);
	free (tok->str);
	tok->str = sub;
}

/**
 * Parses a command string and stores it in command structures within a tree.
 * @param str char*: The command string to parse.
 * @param tok t_tok*: The current token.
 * @param shell t_shell*: The shell environment.
 * @return t_cmd*: The root of the command tree.
 */
t_cmd	*parsecmd(char *str, t_tok *tok, t_shell *shell)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	char		*substr;
	t_tok		tok2;

	ret = NULL;
	if (tok->tok == -1)
	{
		ret = make_execcmd();
		cmd = (t_execcmd *)ret;
		parsexe(cmd, str, shell);
	}
	if (ft_tofile(tok->tok) == 1)
	{
		substr = ft_delstr(str, tok->s_loc, tok->cut);
		get_token(&tok2, substr);
		expand_file_name(tok, shell);
		ret = make_redircmd(parsecmd(substr, &tok2, shell), tok->str, tok->tok);
		free (substr);
	}
	return (ret);
}

/**
 * Identifies and returns the first token in a string not in quotes.
 * @param tok t_tok*: The token structure to update with token information.
 * @param str char*: The string to search for tokens.
 */
void	get_token(t_tok *tok, char *str)
{
	int		i;
	int		*q_check;
	int		*p_check;

	i = 0;
	q_check = parse_quotes(str);
	p_check = parse_para(str);
	while (str[i] != '\0' && (ft_isspace(str[i])
			|| !(ft_istok(str[i]) != -1 && q_check[i] == 0)))
		i++;
	tok->s_loc = i;
	if (ft_istok(str[i]) != RIN && ft_istok(str[i]) != ROUT)
		tok->tok = ft_istok(str[i]);
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
	{
		ft_putendl_fd("here string not supported", STDERR_FILENO);
		tok->tok = FERR;
	}
	else
		get_redir_token(tok, i, str);
	free (q_check);
	free (p_check);
}
