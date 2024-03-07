/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:44:44 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/07 13:45:01 by mevonuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// locates an & if it is not in quotes
int	is_back(char *str, t_tok *tok)
{
	int	i;
	int	*q_check;

	q_check = parse_quotes(str);
	i = 0;
	while (str[i] != '\0' && !(str[i] == '&' && q_check[i] == 0))
		i++;
	free (q_check);
	if (i < (int)ft_strlen(str))
	{
		tok->s_loc = i + 1;
		tok->tok = AND;
		tok->len = (int)ft_strlen(str) - (i + 1);
		return (1);
	}
	return (0);
}

// trims string so it only contains stuff after the pipe, to the right
char	*after_back(char *str, t_tok *tok)
{
	char	*next_cmd;

	next_cmd = ft_substr(str, tok->s_loc, tok->len);
	return (next_cmd);
}

// splits commands into pipe structure if back is between two commands
t_cmd	*parse_back(char *str, t_tok *tok)
{
	t_cmd		*ret;
	char		*s_left;
	char		*s_right;
	t_tok		tok_right;

	s_left = ft_substr(str, 0, tok->s_loc - 1);
	s_right = after_back(str, tok);
	// need to change the way I get here similar to pipe
	// if s_right is empty, need to make back
	// if s_right is occupied, make pipe
	// nothing lower down is right
	get_token(tok, s_left);
	if (is_back(s_right, &tok_right) == 1)
		ret = make_pipecmd(parsecmd(s_left, tok),
				parse_pipe(s_right, &tok_right));
	else
	{
		get_token(&tok_right, s_right);
		ret = make_pipecmd(parsecmd(s_left, tok),
				parsecmd(s_right, &tok_right));
	}
	free (s_left);
	free (s_right);
	return (ret);
}
