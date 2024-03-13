/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:34:01 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/11 17:52:29 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if there is a var before quotes
int	var_quote_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		if (str[i] == '"')
			return (2);
		i++;
	}
	return (0);
}

// stores all commands in command structures in a tree
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
		if (var_quote_check(str) == 1)
		{
			substr = expand_var(str, shell);
			ft_printf("sub %s\n", substr);
			cmd->argv = clean_quotes(p_spliter(substr), shell);
			free (substr);
		}
		else
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

// trim off first set of parentheses
char	*trim_para(char *str)
{
	int	i;
	int	j;
	int	*q_check;
	int	len;
	int	done;

	len = (int)ft_strlen(str);
	q_check = parse_quotes(str);
	i = 0;
	j = 1;
	done = 0;
	while (j < len)
	{
		if (done == 0 && str[j] == ')' && q_check[j] == 0)
		{
			done = 1;
			j++;
		}
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free (q_check);
	return (str);
}

// removes parentheses or flags error if there is more stuff in the line
t_cmd	*parse_paren(char *str, t_shell *shell)
{
	t_cmd		*cmd;
	int			i;

	if (str[ft_strlen(str) - 1] == ')')
	{
		str = trim_para(str);
		cmd = lexer(str, shell);
	}
	else
	{
		i = 0;
		while (str[i] != ')' && str[i] != '\0')
			i++;
		i++;
		while (ft_isspace(str[i]) == 1)
			i++;
		ft_printf("syntax error near unexpected token \'%c\'\n", str[i]);
		cmd = NULL;
	}
	return (cmd);
}

// checks if input is NULL
// checks if parenthesis and quotes are balanced
// parses command into simple "tree" based on tokens
// returns tree
t_cmd	*lexer(char *str, t_shell *shell)
{
	t_cmd		*cmd;
	t_tok		tok;
	char		*strim;

	if (str == NULL)
		return (NULL);
	if (balance_pandq(str) == 0)
		return (NULL);
	if (has_first_level(str, &tok) == 1)
		cmd = parse_ifthen(str, &tok, shell);
	else if (is_pipe(str, &tok) == 1)
		cmd = parse_pipe(str, &tok, shell);
	else
	{
		strim = ft_strtrim(str, " ");
		if (strim[0] == '(')
			cmd = parse_paren(strim, shell);
		else
		{
			get_token(&tok, strim);
			cmd = parsecmd(strim, &tok, shell);
		}
		free (strim);
	}
	return (cmd);
}
