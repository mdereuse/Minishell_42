/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 16:16:01 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 17:10:59 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			actualize_variable(char *arg, char *key, t_mini *mini)
{
	char	*value;
	char	*previous_value;
	char	*tmp;
	int		ret;

	if (!is_initialized(arg))
		return (SUCCESS);
	if (!(value = get_value_from_env_line(arg)))
		return (ENOMEM);
	if (is_modified(arg) && (previous_value = get_env_var_value(key, mini)))
	{
		tmp = value;
		if (!(value = ft_strjoin(previous_value, value)))
		{
			free(tmp);
			return (ENOMEM);
		}
		free(tmp);
	}
	if (SUCCESS != (ret = set_env_var_value(key, value, mini)))
	{
		free(value);
		return (ret);
	}
	return (SUCCESS);
}

int			export_new_variable(char *arg, char *key, t_mini *mini)
{
	int		ret;

	if (SUCCESS != (ret = add_new_env_var(arg, mini)))
		return (ret);
	if (!is_initialized(arg)
			&& ((!ft_strcmp(key, "PWD") && mini->pwd)
				|| (!ft_strcmp(key, "OLDPWD") && mini->oldpwd))
			&& (SUCCESS != (ret = restore_pwd_and_oldpwd(key, mini))))
		return (ret);
	return (SUCCESS);
}

int			export(char *arg, char *key, t_mini *mini)
{
	int		ret;

	if (!key_not_found(key, mini))
	{
		if (SUCCESS != (ret = actualize_variable(arg, key, mini)))
			return (ret);
	}
	else
	{
		if (SUCCESS != (ret = export_new_variable(arg, key, mini)))
			return (ret);
	}
	return (SUCCESS);
}

int			manage_export_arg(char *arg, t_mini *mini)
{
	char	*key;
	int		ret;

	if (!(key = get_key_from_env_line(arg)))
		return (ENOMEM);
	if (!check_key_ok(key))
	{
		free(key);
		return (ERROR_INVALID_KEY);
	}
	if (SUCCESS != (ret = export(arg, key, mini)))
	{
		free(key);
		return (ret);
	}
	if (!ft_strcmp(key, "PATH") && SUCCESS != (ret = actualize_path(mini)))
	{
		free(key);
		return (ERROR_FTL);
	}
	free(key);
	if (SUCCESS != (ret = actualize_env_tab(mini)))
		return (ERROR_FTL);
	return (SUCCESS);
}

void		display_export(t_command *command, t_mini *mini)
{
	t_list		*current;
	t_env_var	*env_var;

	current = mini->env_list;
	while (current)
	{
		env_var = current->content;
		ft_putstr_fd("declare -x ", command->exit_fd);
		ft_putstr_fd(env_var->key, command->exit_fd);
		if (env_var->value)
		{
			ft_putstr_fd("=", command->exit_fd);
			ft_putstr_fd("\"", command->exit_fd);
			ft_putstr_fd(env_var->value, command->exit_fd);
			ft_putstr_fd("\"", command->exit_fd);
		}
		ft_putstr_fd("\n", command->exit_fd);
		current = current->next;
	}
}
