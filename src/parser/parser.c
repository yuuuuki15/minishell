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
void	parsexe(t_execcmd *cmd, char *str, t_shell *shell)
{
	char		*substr;

	if (var_quote_check(str) == 1)
	{
		substr = expand_var(str, shell);
		cmd->argv = p_spliter(substr);
		clean_quotes(cmd->argv, shell);
		free (substr);
	}
	else
	{
		cmd->argv = p_spliter(str);
		clean_quotes(cmd->argv, shell);
	}
}

// expand var and remove quotes in file name
void	expand_file_name(t_tok *tok, t_shell *shell)
{
	char	*sub;

	sub = expand_var(tok->str, shell);
	free (tok->str);
	tok->str = remove_quotes(sub);
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
		ft_printf("here string not supported\n");
		tok->tok = FERR;
	}
	else
		get_redir_token(tok, i, str);
	free (q_check);
	free (p_check);
}
