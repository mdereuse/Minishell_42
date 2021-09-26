/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:19:06 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 17:14:04 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unset_args(t_command *command)
{
	int		i;

	i = 1;
	while (command->argv[i])
	{
		if (!check_key_ok(command->argv[i]))
		{
			put_error_msg(ERROR_INVALID_KEY, "unset", command->argv[i]);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int			compare_env_var(t_env_var *env_var, char *key)
{
	return (ft_strcmp(env_var->key, key));
}

int			builtin_unset(t_command *command, t_mini *mini)
{
	int		i;
	int		ret;

	if (!command->argv[1])
		return (SUCCESS);
	i = 1;
	while (command->argv[i])
	{
		ft_lstremove_if(&(mini->env_list), command->argv[i], compare_env_var,
																clean_env_var);
		if (!ft_strcmp(command->argv[i], "PATH")
				&& (SUCCESS != (ret = actualize_path(mini))))
		{
			put_error_msg(ERROR_FTL, "unset", NULL);
			quit(ERROR_FTL, mini);
		}
		i++;
	}
	if (SUCCESS != (ret = actualize_env_tab(mini)))
	{
		put_error_msg(ERROR_FTL, "unset", NULL);
		quit(ERROR_FTL, mini);
	}
	return (check_unset_args(command));
}
