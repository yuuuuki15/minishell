/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:07:43 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/21 12:14:27 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expands lexer for line count, handling single commands, quotes, parentheses,
 * and redirects.
 * @param str char*: The input string to be lexed.
 * @param shell t_shell*: The shell environment.
 * @return t_cmd*: The command structure after parsing.
 * @error Returns NULL if an error occurs during parsing.
 */
static t_cmd	*lexer_helper(char *str, t_shell *shell)
{
	t_cmd		*cmd;
	t_tok		tok;
	char		*strim;

	strim = ft_strtrim(str, " ");
	if (strim[0] == '(')
		cmd = parse_paren(strim, shell);
	else
	{
		get_token(&tok, strim);
		if (tok.tok == FERR)
		{
			free (strim);
			return (NULL);
		}
		cmd = parsecmd(strim, &tok, shell);
	}
	if (strim)
		free (strim);
	return (cmd);
}

/**
 * Checks for starting with pipe or and, indicating syntax error.
 * @param str char*: The input string to check.
 * @param shell t_shell*: The shell environment.
 * @return int: 1 if an error is found, 0 otherwise.
 */
static int	bad_pipe_and(char *str, t_shell *shell)
{
	char	*temp;

	temp = ft_strtrim(str, " ");
	if (temp[0] == '|' || temp[0] == '&')
	{
		ft_putendl_fd("unexpected token", STDERR_FILENO);
		shell->exit_status = 2;
		free (temp);
		return (1);
	}
	free (temp);
	return (0);
}

/**
 * Finds the next token in the string, considering quotes.
 * @param i int: The current index in the string.
 * @param str char*: The input string.
 * @param q_check int*: Array indicating if a character is within quotes.
 * @param shell t_shell*: The shell environment.
 * @return int: 1 if an unexpected token is found, 0 otherwise.
 */
static int	next_tok(int i, char *str, int *q_check, t_shell *shell)
{
	int	j;

	j = 0;
	if ((ft_isfulltok(str, i) != -1 || ft_istok(str[i]) != -1)
		&& q_check[i] == 0)
	{
		j = 1;
		if (ft_isfulltok(str, i) != -1)
			j++;
		while (str[i + j] != '\0' && ft_isspace(str[i + j]) == 1
			&& q_check[i + j] == 0)
			j++;
		if (i + j < (int)ft_strlen(str) && q_check[i + j] == 0
			&& ((str[i + j] == '|' || str[i + j] == '&'
			|| str[i + j] == '(' || str[i + j] == ')')))
		{
			ft_putendl_fd("unexpected token", STDERR_FILENO);
			shell->exit_status = 2;
			return (1);
		}
	}
	return (0);
}

/**
 * Checks for repeating tokens that are not allowed.
 * @param str char*: The input string to check.
 * @param shell t_shell*: The shell environment.
 * @return int: 1 if repeating tokens are found, 0 otherwise.
 */
static int	repeating_tok(char *str, t_shell *shell)
{
	int	i;
	int	*q_check;

	q_check = parse_quotes(str);
	i = 0;
	while (str[i] != '\0')
	{
		if ((ft_isfulltok(str, i) != -1 || ft_istok(str[i]) != -1)
			&& q_check[i] == 0)
		{
			if (next_tok(i, str, q_check, shell) == 1)
			{
				free (q_check);
				return (1);
			}
		}
		i++;
	}
	free (q_check);
	return (0);
}

/**
 * Main lexer function. Checks if input is NULL, if parenthesis and quotes are
 * balanced, parses command into a simple "tree" based on tokens.
 * @param str char*: The input string to be lexed.
 * @param shell t_shell*: The shell environment.
 * @return t_cmd*: The command structure after parsing.
 * @error Returns NULL if an error occurs or if checks fail.
 */
t_cmd	*lexer(char *str, t_shell *shell)
{
	t_cmd		*cmd;
	t_tok		tok;

	if (str == NULL)
		return (NULL);
	if (balance_pandq(str) == 0)
		return (NULL);
	if (bad_pipe_and(str, shell) != 0)
		return (NULL);
	if (repeating_tok(str, shell) == 1)
		return (NULL);
	if (has_first_level(str, &tok) == 1)
		cmd = parse_ifthen(str, &tok, shell);
	else if (is_pipe(str, &tok) == 1)
		cmd = parse_pipe(str, &tok, shell);
	else
		cmd = lexer_helper(str, shell);
	return (cmd);
}
