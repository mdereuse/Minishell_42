/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:26:09 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 19:33:35 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*get_key_from_env_line(char *env_line)
{
	int		size;
	int		i;
	char	*key;

	size = 0;
	while (env_line[size] && !is_end_key(env_line, size))
		size++;
	if (!(key = (char*)malloc(sizeof(*key) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		key[i] = env_line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char				*get_value_from_env_line(char *env_line)
{
	int		size;
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	i = env_line[i] == '=' ? i + 1 : i;
	size = 0;
	while (env_line[i + size])
		size++;
	if (!(value = (char*)malloc(sizeof(*value) * (size + 1))))
		return (NULL);
	j = 0;
	while (env_line[i])
		value[j++] = env_line[i++];
	value[j] = '\0';
	return (value);
}

static t_env_var	*create_new_env_var(char *env_line)
{
	t_env_var	*new_env_var;

	if (!(new_env_var = (t_env_var*)malloc(sizeof(*new_env_var))))
		return (NULL);
	new_env_var->key = NULL;
	new_env_var->value = NULL;
	if (!(new_env_var->key = get_key_from_env_line(env_line)))
	{
		clean_env_var(new_env_var);
		return (NULL);
	}
	if (is_initialized(env_line)
		&& !(new_env_var->value = get_value_from_env_line(env_line)))
	{
		clean_env_var(new_env_var);
		return (NULL);
	}
	return (new_env_var);
}

static int			sort_env_var(void *content1, void *content2)
{
	t_env_var	*env_var1;
	t_env_var	*env_var2;
	char		*key1;
	char		*key2;

	env_var1 = content1;
	env_var2 = content2;
	key1 = env_var1->key;
	key2 = env_var2->key;
	return (ft_strcmp(key1, key2));
}

int					add_new_env_var(char *env_line, t_mini *mini)
{
	t_env_var	*new_env_var;
	t_list		*new_element;

	if (!(new_env_var = create_new_env_var(env_line)))
		return (ENOMEM);
	if (!(new_element = ft_lstnew(new_env_var)))
	{
		clean_env_var(new_env_var);
		return (ENOMEM);
	}
	ft_lstadd_sort(&(mini->env_list), new_element, sort_env_var);
	return (SUCCESS);
}
