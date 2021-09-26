/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_actualization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 16:39:29 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:09:36 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			actualize_env_tab(t_mini *mini)
{
	int		ret;

	if (mini->env_tab)
	{
		ft_clean_tab(mini->env_tab);
		mini->env_tab = NULL;
	}
	if (SUCCESS != (ret = set_env_tab(mini)))
	{
		put_error_msg(ret, "actualizing environment", NULL);
		return (ret);
	}
	return (SUCCESS);
}

int			actualize_path(t_mini *mini)
{
	int		ret;

	if (mini->path)
	{
		ft_clean_tab(mini->path);
		mini->path = NULL;
	}
	if (SUCCESS != (ret = set_path(mini)))
	{
		put_error_msg(ret, "actualizing path", NULL);
		return (ret);
	}
	return (SUCCESS);
}
