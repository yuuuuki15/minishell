/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:34:01 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/10 17:43:04 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stores all commands in command structures in a tree
t_cmd	*parsecmd(char *str, t_tok *tok, t_shell *shell)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	char		*substr;
	t_tok		tok2;

	if (tok->tok == -1)
	{
		ret = make_execcmd();
		cmd = (t_execcmd *)ret;
		cmd->argv = clean_quotes(p_spliter(str), shell);
	}
	if (ft_tofile(tok->tok) == 1)
	{
		substr = ft_delstr(str, tok->s_loc, tok->cut);
		get_token(&tok2, substr);
		ret = make_redircmd(parsecmd(substr, &tok2, shell), tok->str, tok->tok);
		free (substr);
	}
	return (ret);
}

// extracts file name from string
void	get_file_name(t_tok *tok, int i, int size, char *str)
{
	i++;
	tok->len = 0;
	if (str[i] == '<' || str[i] == '>')
		ft_printf("syntax error near unexpected token \'%c\'\n", str[i]);
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
	if (ft_istok(str[i]) == RIN && ft_istok(str[i + 1]) == RIN)
	{
		i++;
		tok->tok = RHERE;
		size++;
	}
	else if (ft_istok(str[i]) == RIN && ft_istok(str[i + 1]) != RIN)
		tok->tok = RIN;
	else if (ft_istok(str[i]) == ROUT && ft_istok(str[i + 1]) != ROUT)
		tok->tok = ROUT;
	else if (ft_istok(str[i]) == ROUT && ft_istok(str[i + 1]) == ROUT)
	{
		tok->tok = ROUTA;
		i++;
		size++;
	}
	get_file_name(tok, i, size, str);
}

// extracts para phrase from string
void	get_para_tok(t_tok *tok, int i, char *str, int *p_check)
{
	i++;
	tok->len = 0;
	while (p_check[i] == 1)
	{
		tok->len++;
		i++;
	}
	tok->str = ft_substr(str, tok->s_loc + 1, tok->len);
	tok->size = tok->len;
	tok->cut = i;
	ft_printf("in parentheses: %s\n", tok->str);
}

// identifies and returns the first token in a string that is not in quotes
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
		str = ft_substr(str, 0, tok->s_loc);
		str[tok->s_loc] = '\0';
		tok->tok = -1;
	}
	else
		get_redir_token(tok, i, str);
	free (q_check);
	free (p_check);
}

// check balance of () and quotes
int	balance_pandq(char *str)
{
	int	ret;

	ret = 1;
	if (balance_quotes(str) == 0)
		ret = 0;
	if (balance_para(str) == -1)
		ret = 0;
	if (ret == 0)
		ft_printf("Parsing error! Check your quotes and parentheses!\n");
	return (ret);
}

// checks if input is NULL
// checks if parenthesis and quotes are balanced
// parses command into simple "tree" based on tokens
// returns tree
t_cmd	*lexer(char *str, t_shell *shell)
{
	t_cmd		*cmd;
	t_tok		tok;

	if (str == NULL)
		return (NULL);
	if (balance_pandq(str) == 0)
		return (NULL);
	if (has_first_level(str, &tok) == 1)
		cmd = parse_ifthen(str, &tok, shell);
	else
	{
		if (is_pipe(str, &tok) == 1)
			cmd = parse_pipe(str, &tok, shell);
		else
		{
			get_token(&tok, str);
			cmd = parsecmd(str, &tok, shell);
		}
	}
	return (cmd);
}
