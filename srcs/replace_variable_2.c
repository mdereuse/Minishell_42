/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 20:52:20 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/10 20:54:11 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_value_and_size_key_lst_status(char **value, int *size_key,
		t_mini *mini)
{
	*size_key = 1;
	if (!(*value = ft_itoa(mini->lst_status)))
		return (ENOMEM);
	return (SUCCESS);
}

int		set_value_and_size_key_digit(char **value, int *size_key)
{
	*size_key = 1;
	if (!(*value = ft_strdup("")))
		return (ENOMEM);
	return (SUCCESS);
}

int		set_value_and_size_key_quote(char **value, int *size_key)
{
	*size_key = 0;
	if (!(*value = ft_strdup("")))
		return (ENOMEM);
	return (SUCCESS);
}

int		set_value_and_size_key_lst_word(char **value, int *size_key,
		t_mini *mini)
{
	*size_key = 1;
	if (!(*value = ft_strdup(mini->lst_word)))
		return (ENOMEM);
	return (SUCCESS);
}

int		set_value_and_size_key_default(char *str, char **value, int *size_key,
		t_mini *mini)
{
	char	*key;
	int		ret;

	if (!(key = find_env_variable_key(str)))
		return (ENOMEM);
	*size_key = ft_strlen(key);
	ret = get_dup_env_var_value(value, key, mini);
	free(key);
	if (ERROR_KEY_NOT_FOUND == ret || ERROR_VALUE_NOT_FOUND == ret)
	{
		if (!(*value = ft_strdup("")))
			return (ENOMEM);
	}
	else if (SUCCESS != ret)
		return (ret);
	return (SUCCESS);
}
