/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 10:08:36 by mariedere         #+#    #+#             */
/*   Updated: 2020/04/15 13:05:34 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			set_path(t_mini *mini)
{
	char		*path_str;
	char		**path_tab;

	if (!(path_str = get_env_var_value("PATH", mini)))
	{
		mini->path = NULL;
		return (SUCCESS);
	}
	if (!(path_tab = ft_split(path_str, ':')))
		return (ENOMEM);
	mini->path = path_tab;
	return (SUCCESS);
}
