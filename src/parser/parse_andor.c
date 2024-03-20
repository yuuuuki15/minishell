/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_andor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:44:44 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:46:08 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extracts the substring after a specific token.
 * @param str char*: The input string.
 * @param tok t_tok*: The token indicating where to start the substring.
 * @return char*: The substring after the token.
 */
static char	*after_token(char *str, t_tok *tok)
{
	char	*next_cmd;

	next_cmd = ft_substr(str, tok->s_loc + tok->size - 1, tok->len);
	return (next_cmd);
}

/**
 * Determines the type of operation based on the token and following string.
 * @param str char*: The input string.
 * @param tok t_tok*: The current token.
 * @return int: The type of operation, IFOR or the token's type.
 */
static int	get_type(char *str, t_tok *tok)
{
	char	*temp;
	char	*s_right;
	int		type;

	s_right = after_token(str, tok);
	temp = ft_strtrim(s_right, " ");
	if (tok->tok == AND && ft_strlen(temp) > 0)
		type = IFOR;
	else
		type = tok->tok;
	free (s_right);
	free (temp);
	return (type);
}

/**
 * Checks if a token is left hanging without a command.
 * @param str char*: The input string.
 * @param type int: The type of the current token.
 * @param shell t_shell*: The shell environment.
 * @return int: 1 if the token is hanging, 0 otherwise.
 */
static int	hanging_token(char *str, int type, t_shell *shell)
{
	char	*temp;
	int		ret;

	ret = 0;
	temp = ft_strtrim(str, " ");
	if (ft_strlen(temp) == 0)
	{
		if (type != AND)
		{
			ft_putendl_fd("Dangling token not supported!", STDERR_FILENO);
			shell->exit_status = 2;
		}
		ret = 1;
	}
	free (temp);
	return (ret);
}

/**
 * Parses a string into a command structure based on if-then logic.
 * @param str char*: The input string.
 * @param tok t_tok*: The current token.
 * @param shell t_shell*: The shell environment.
 * @return t_cmd*: The parsed command structure.
 * @error Returns NULL if an error occurs during parsing.
 */
t_cmd	*parse_ifthen(char *str, t_tok *tok, t_shell *shell)
{
	t_cmd		*ret;
	char		*s_left;
	char		*s_right;
	t_tok		tok_right;
	int			type;

	s_left = ft_substr(str, 0, tok->s_loc - 1);
	s_right = after_token(str, tok);
	type = get_type(str, tok);
	if (hanging_token(s_right, type, shell) == 1 && type != AND)
		ret = NULL;
	else if (has_first_level(s_right, &tok_right) == 1)
		ret = make_listcmd(lexer(s_left, shell),
				parse_ifthen(s_right, &tok_right, shell), type);
	else if (type == BACK)
		ret = make_backcmd(lexer(s_left, shell));
	else
		ret = make_listcmd(lexer(s_left, shell), lexer(s_right, shell), type);
	free (s_left);
	free (s_right);
	return (ret);
}
