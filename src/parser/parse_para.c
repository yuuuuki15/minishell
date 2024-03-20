/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_para.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:46:42 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/20 11:31:54 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sets values to 2 if para, 1 if inside ()
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

// makes an integer array that denotes if in quotes and quote type
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

// trim off first set of parentheses
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

// count number of lowest level parentheses
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

// removes parentheses or flags error if there is more stuff in the line
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
