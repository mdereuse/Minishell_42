/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 09:24:16 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 16:21:20 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_var_str_size(t_env_var *env_var)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (env_var->key[i++])
		size++;
	i = 0;
	while (env_var->value[i++])
		size++;
	size++;
	return (size);
}

static char	*get_env_var_str(t_env_var *env_var)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	size = get_env_var_str_size(env_var);
	if (!(str = (char*)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (env_var->key[i])
		str[j++] = env_var->key[i++];
	str[j++] = '=';
	i = 0;
	while (env_var->value[i])
		str[j++] = env_var->value[i++];
	str[j] = '\0';
	return (str);
}

static int	get_env_tab_size(t_mini *mini)
{
	int		size;
	t_list	*current;

	size = 0;
	current = mini->env_list;
	while (current)
	{
		if (!empty_variable(current->content))
			size++;
		current = current->next;
	}
	return (size);
}

static int	fill_env_tab(t_mini *mini)
{
	int			i;
	t_list		*current;
	char		*lst_word;

	i = 0;
	current = mini->env_list;
	while (current)
	{
		if (!empty_variable(current->content))
		{
			if (!(mini->env_tab[i] = get_env_var_str(current->content)))
			{
				ft_clean_tab_index(mini->env_tab, i);
				mini->env_tab = NULL;
				return (ENOMEM);
			}
			i++;
		}
		current = current->next;
	}
	if (!(lst_word = ft_strjoin("_=", mini->lst_word)))
		return (ENOMEM);
	mini->env_tab[i++] = lst_word;
	mini->env_tab[i] = NULL;
	return (SUCCESS);
}

int			set_env_tab(t_mini *mini)
{
	if (!(mini->env_tab = (char**)malloc(sizeof(*(mini->env_tab))
											* (get_env_tab_size(mini) + 2))))
		return (ENOMEM);
	return (fill_env_tab(mini));
}
