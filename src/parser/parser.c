/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:34:01 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/09 15:00:37 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stores all commands in command structures in a tree
t_cmd	*parsecmd(char *str, t_tok *tok, t_shell *g_shell)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	char		*substr;
	t_tok		tok2;

	if (tok->tok == -1)
	{
		ret = make_execcmd();
		cmd = (t_execcmd *)ret;
		cmd->argv = clean_quotes(p_spliter(str), g_shell);
	}
	if (tok->tok == AND)
	{
		// this should not be passed here, it should be passed to parse_cak to check for pipe-like behavior
		ft_printf("back\n");
		str = ft_strtrim(str, "&");
		get_token(tok, str);
		ret = make_backcmd(parsecmd(str, tok, g_shell));
	}
	if (ft_tofile(tok->tok) == 1)
	{
		substr = ft_delstr(str, tok->s_loc, tok->cut);
		get_token(&tok2, substr);
		ret = make_redircmd(parsecmd(substr, &tok2, g_shell), tok->str, tok->tok);
		free (substr);
	}
	return (ret);
}

// extracts file name from string
void	get_file_name(t_tok *tok, int i, int size, char *str)
{
	i++;
	tok->len = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
	{
		tok->len++;
		i++;
	}
	while (str[i] != '\0' && ft_isspace(str[i]) == 0)
	{
		tok->len++;
		i++;
	}
	tok->str = ft_strtrim(ft_substr(str, tok->s_loc + size, tok->len), " ");
	tok->size = tok->len + size - 1;
	tok->cut = i;
}

// get information for redirection tokens
void	get_redir_token(t_tok *tok, int i, char *str)
{
	int	size;

	size = 1;
	if (ft_issym(str[i]) == RIN && ft_issym(str[i + 1]) == RIN)
	{
		i++;
		tok->tok = RHERE;
		size++;
	}
	else if (ft_issym(str[i]) == RIN && ft_issym(str[i + 1]) != RIN)
		tok->tok = RIN;
	else if (ft_issym(str[i]) == ROUT && ft_issym(str[i + 1]) != ROUT)
		tok->tok = ROUT;
	else if (ft_issym(str[i]) == ROUT && ft_issym(str[i + 1]) == ROUT)
	{
		tok->tok = ROUTA;
		i++;
		size++;
	}
	get_file_name(tok, i, size, str);
}

// identifies and returns the first token in a string that is not in quotes
void	get_token(t_tok *tok, char *str)
{
	int		i;
	int		*q_check;

	i = 0;
	q_check = parse_quotes(str);
	while (str[i] != '\0' && (ft_isspace(str[i])
			|| !(ft_issym(str[i]) != -1 && q_check[i] == 0)))
		i++;
	tok->s_loc = i;
	if (ft_issym(str[i]) != RIN && ft_issym(str[i]) != ROUT)
		tok->tok = ft_issym(str[i]);
	else
		get_redir_token(tok, i, str);
	free (q_check);
}

// currently checks if input is NULL
// checks if quotes are balanced
// checks for pipe and devides accordingly
// parses command into simple "tree" based on tokens
// prints tree and then returns tree
t_cmd	*lexer(char *str, t_shell *g_shell)
{
	t_cmd		*cmd;
	t_tok		tok;

	if (str == NULL)
		return (NULL);
	if (balance_quotes(str) == 0)
	{
		ft_printf("error: Unbalanced quotes!\n");
		return (NULL);
	}
	if (is_pipe(str, &tok) == 1)
		cmd = parse_pipe(str, &tok);
	else
	{
		get_token(&tok, str);
		cmd = parsecmd(str, &tok, g_shell);
	}
	print_tree(cmd);
	return (cmd);
}
