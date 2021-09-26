/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 05:47:18 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 16:45:57 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env_var_value(char *key, t_mini *mini)
{
	t_list		*current;
	t_env_var	*env_var;

	current = mini->env_list;
	while (current)
	{
		env_var = current->content;
		if (!ft_strcmp(key, env_var->key))
			return (env_var->value);
		current = current->next;
	}
	return (NULL);
}

int			get_dup_env_var_value(char **str, char *key, t_mini *mini)
{
	t_list		*current;
	t_env_var	*env_var;

	current = mini->env_list;
	while (current)
	{
		env_var = current->content;
		if (!ft_strcmp(key, env_var->key))
		{
			if (empty_variable(env_var))
				return (ERROR_VALUE_NOT_FOUND);
			if (!(*str = ft_strdup(env_var->value)))
				return (ENOMEM);
			return (SUCCESS);
		}
		current = current->next;
	}
	return (ERROR_KEY_NOT_FOUND);
}

int			set_env_var_value(char *key, char *new_value, t_mini *mini)
{
	t_list		*current;
	t_env_var	*env_var;

	current = mini->env_list;
	while (current)
	{
		env_var = current->content;
		if (!ft_strcmp(key, env_var->key))
		{
			if (env_var->value)
				free(env_var->value);
			env_var->value = new_value;
			return (SUCCESS);
		}
		current = current->next;
	}
	return (ERROR_KEY_NOT_FOUND);
}
