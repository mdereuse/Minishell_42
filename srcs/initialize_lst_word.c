/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lst_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:34:11 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/20 06:12:28 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			initialize_lst_word(t_mini *mini)
{
	int		ret;

	if (value_not_found("_", mini))
	{
		if (!(mini->lst_word = ft_strdup("minishell")))
			return (ENOMEM);
	}
	else if (SUCCESS != (ret = get_dup_env_var_value(&(mini->lst_word),
					"_", mini)))
		return (ret);
	ft_lstremove_if(&(mini->env_list), "_", compare_env_var, clean_env_var);
	return (SUCCESS);
}
