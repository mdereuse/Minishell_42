/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:47:34 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/20 07:34:06 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_value_and_size_key(char *str, char **value, int *size_key,
			t_mini *mini)
{
	if (!ft_strncmp(str, "$?", 2))
		return (set_value_and_size_key_lst_status(value, size_key, mini));
	else if (!ft_strncmp(str, "$_", 2))
		return (set_value_and_size_key_lst_word(value, size_key, mini));
	else if (str[1] && ft_isdigit(str[1]))
		return (set_value_and_size_key_digit(value, size_key));
	else if (str[1] && (str[1] == '\'' || str[1] == '\"'))
		return (set_value_and_size_key_quote(value, size_key));
	else
		return (set_value_and_size_key_default(str, value, size_key, mini));
}

static int	replace_var_key(char **arg, int index, char *value,
			int size_key)
{
	char	*tmp;

	tmp = *arg;
	if (!(*arg = create_new_arg_with_var(*arg, index, size_key, value)))
	{
		*arg = tmp;
		return (ENOMEM);
	}
	free(tmp);
	return (SUCCESS);
}

static int	remove_empty_arg(char ***argv, int index)
{
	char	**tmp;
	char	*to_remove;

	tmp = *argv;
	to_remove = (*argv)[index];
	if (!(*argv = ft_rm_from_tab(*argv, index)))
	{
		*argv = tmp;
		return (ENOMEM);
	}
	free(tmp);
	free(to_remove);
	return (SUCCESS);
}

int			replace_variable_word(char **word, t_mini *mini)
{
	int		i;
	int		size_key;
	char	*value;
	int		ret;

	i = 0;
	while ((*word)[i])
	{
		if (is_new_variable(*word, i))
		{
			if (SUCCESS != (ret = set_value_and_size_key(*word + i, &value,
							&size_key, mini)))
				return (ret);
			if (SUCCESS != (ret = replace_var_key(word, i, value, size_key)))
			{
				free(value);
				return (ret);
			}
			i += ft_strlen(value);
			free(value);
		}
		else
			i++;
	}
	return (SUCCESS);
}

int			replace_variable_command(t_command *command, t_mini *mini)
{
	int		i;
	int		ret;

	i = 0;
	while (command->argv[i])
	{
		if (SUCCESS != (ret = replace_variable_word(command->argv + i, mini)))
			return (ret);
		if (!command->argv[i][0])
		{
			if (SUCCESS != (ret = remove_empty_arg(&(command->argv), i)))
				return (ret);
		}
		else
			i++;
	}
	return (SUCCESS);
}
