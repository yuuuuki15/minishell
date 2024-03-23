/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:39:26 by mevonuk           #+#    #+#             */
/*   Updated: 2024/03/23 09:28:55 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Frees an environment node.
 * @param ptr t_env*: Pointer to the environment node to be freed.
 */
void	free_node(t_env *ptr)
{
	if (ptr)
	{
		if (ptr->key)
			free(ptr->key);
		if (ptr->value)
			free(ptr->value);
		free(ptr);
	}
}

/**
 * Unsets an environment variable.
 * @param key char*: The key of the environment variable to unset.
 * @param shell t_shell*: The shell containing the environment variables.
 * Removes the environment variable matching the given key from the shell's
 * environment list and frees the associated memory.
 */
void	ft_unset_env(char *key, t_shell *shell)
{
	t_env	*curr;
	t_env	*to_delete;

	curr = shell->env;
	to_delete = NULL;
	if (curr == NULL)
		return ;
	if (ft_strcmp(curr->key, key) == 0)
	{
		shell->env = curr->next;
		free_node(curr);
		return ;
	}
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			to_delete = curr->next;
			curr->next = curr->next->next;
			free_node(to_delete);
			return ;
		}
		curr = curr->next;
	}
}
int	ft_add_env_not_exported(char *key, t_shell *shell)
{
	t_env	*new;
	t_env	*curr;

	if (ft_is_valid_identifier(key) == 0)
		return (1);
	if (ft_get_env(key, shell) != NULL)
		return (0);
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (1);
	new->key = key;
	new->value = ft_strdup("");
	new->next = NULL;
	new->exported = 0;
	curr = shell->env;
	if (curr == NULL)
	{
		shell->env = new;
		return (0);
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	return (0);
}

char	*ft_get_key_with_flag(char *str, int *plus_equal_flag)
{
	char	*key_end;
	char	*ret;
	int		key_length;

	*plus_equal_flag = 0;
	key_end = ft_strchr(str, '=');
	if (key_end == NULL)
		return (NULL);
	if (*(key_end - 1) == '+')
	{
		*plus_equal_flag = 1;
		key_length = key_end - str - 1;
	}
	else
	{
		key_length = key_end - str;
	}
	ret = ft_substr(str, 0, key_length);
	return (ret);
}

void	ft_plus_equal_export(char *key, char **value, t_shell *shell)
{
	t_env	*original;
	char	*new_value;
	int		len;

	original = ft_get_env(key, shell);
	if (original == NULL)
		return ;
	len = ft_strlen(original->value) + ft_strlen(*value) + 1;
	new_value = (char *)malloc(len);
	if (new_value == NULL)
		ft_error(ERR_MALLOC);
	ft_strlcpy(new_value, original->value, len);
	ft_strlcat(new_value, *value, len);
	free(*value);
	*value = new_value;
	return ;
}
