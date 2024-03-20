/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_para.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:46:42 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 22:46:57 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sets values in an array to indicate the level of parentheses nesting.
 * @param in_para int*: Array to store parentheses levels.
 * @param str char*: Input string to parse.
 * @param in_quotes int*: Array indicating if a character is within quotes.
 */
static void	set_para_values(int *in_para, char *str, int *in_quotes)
{
	int	openp;
	int	i;
	int	val;

	i = 0;
	val = 2;
	openp = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(' && in_quotes[i] == 0)
		{
			in_para[i] = val++;
			openp = 1;
		}
		else if (str[i] == ')' && in_quotes[i] == 0)
		{
			in_para[i] = --val;
			openp = 0;
		}
		else if (openp == 1)
			in_para[i] = 1;
		i++;
	}
}

/**
 * Creates an integer array indicating the level of parentheses nesting.
 * @param str char*: The string to parse.
 * @return int*: Array indicating the level of parentheses nesting.
 * @error Returns NULL if memory allocation fails.
 */
int	*parse_para(char *str)
{
	int	*in_para;
	int	len;
	int	*in_quotes;

	in_quotes = parse_quotes(str);
	len = ft_strlen(str);
	in_para = (int *) malloc (len * sizeof(int));
	if (in_para == 0)
		return (NULL);
	zero_array(in_para, len);
	set_para_values(in_para, str, in_quotes);
	free (in_quotes);
	return (in_para);
}

/**
 * Trims the first set of parentheses from a string.
 * @param str char*: The string to trim parentheses from.
 * @return char*: The modified string with the first set of parentheses removed.
 */
static char	*trim_para(char *str)
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

/**
 * Counts the number of lowest level parentheses in a string.
 * @param str char*: The string to count parentheses in.
 * @return int: The count of lowest level parentheses.
 */
static int	count_p(char *str)
{
	int	i;
	int	cc;
	int	*p_check;

	p_check = parse_para(str);
	i = 0;
	cc = 0;
	while (str[i] != '\0')
	{
		if (p_check[i] == 2)
			cc++;
		i++;
	}
	free (p_check);
	return (cc);
}

/**
 * Parses parentheses in a string and either removes them or flags an error.
 * @param str char*: The string to parse.
 * @param shell t_shell*: The shell environment.
 * @return t_cmd*: The command structure after parsing.
 * @error Returns NULL if there is a syntax error.
 */
t_cmd	*parse_paren(char *str, t_shell *shell)
{
	t_cmd		*cmd;
	int			i;

	if (count_p(str) == 2 && str[ft_strlen(str) - 1] == ')')
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
		return (NULL);
	}
	return (cmd);
}
