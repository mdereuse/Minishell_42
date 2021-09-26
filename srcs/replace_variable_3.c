/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 20:50:07 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/10 20:52:02 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_arg_size(char *arg, int index, int size_key, char *value)
{
	int		size;
	int		i;
	int		j;

	i = 0;
	size = 0;
	while (i < index)
	{
		size++;
		i++;
	}
	i = arg[i] == '$' ? i + 1 : i;
	j = 0;
	while (arg[i] && j < size_key)
	{
		i++;
		j++;
	}
	while (arg[i++])
		size++;
	if (value)
		size += ft_strlen(value);
	return (size);
}

static void	put_counter_to_zero(int *i, int *j, int *k, int *l)
{
	*i = 0;
	*j = 0;
	*k = 0;
	*l = 0;
}

char		*create_new_arg_with_var(char *old_arg, int index_char,
			int size_key, char *value)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*new_arg;

	if (!(new_arg = (char*)malloc(sizeof(*new_arg)
			* (get_new_arg_size(old_arg, index_char, size_key, value) + 1))))
		return (NULL);
	put_counter_to_zero(&i, &j, &k, &l);
	while (old_arg[i] && i < index_char)
		new_arg[j++] = old_arg[i++];
	if (value)
		while (value[k])
			new_arg[j++] = value[k++];
	i = old_arg[i] == '$' ? i + 1 : i;
	while (old_arg[i] && l < size_key)
	{
		i++;
		l++;
	}
	while (old_arg[i])
		new_arg[j++] = old_arg[i++];
	new_arg[j] = '\0';
	return (new_arg);
}

char		*find_env_variable_key(char *arg)
{
	int		size;
	int		i;
	char	*key;

	if (arg[0] != '$')
		return (NULL);
	arg++;
	size = 0;
	while (arg[size] && !is_end_variable(arg, size))
		size++;
	if (!(key = (char*)malloc(sizeof(*key) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}
