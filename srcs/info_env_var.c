/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 16:42:24 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 16:42:55 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		empty_variable(t_env_var *env_var)
{
	return (!env_var->value);
}

bool		check_key_ok(char *key)
{
	int		i;

	if (!*key || !(ft_isalpha(*key) || *key == '_'))
		return (false);
	i = 0;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

bool		key_not_found(char *key, t_mini *mini)
{
	t_list		*current;
	t_env_var	*env_var;

	current = mini->env_list;
	while (current)
	{
		env_var = current->content;
		if (!ft_strcmp(key, env_var->key))
			return (false);
		current = current->next;
	}
	return (true);
}

bool		value_not_found(char *key, t_mini *mini)
{
	t_list		*current;
	t_env_var	*env_var;

	current = mini->env_list;
	while (current)
	{
		env_var = current->content;
		if (!ft_strcmp(key, env_var->key) && !empty_variable(env_var))
			return (false);
		current = current->next;
	}
	return (true);
}
