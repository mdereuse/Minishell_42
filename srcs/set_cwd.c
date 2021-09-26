/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 03:56:29 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/03 03:58:23 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			set_cwd(t_mini *mini)
{
	char		cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (errno);
	if (!(mini->cwd = ft_strdup(cwd)))
		return (ENOMEM);
	return (SUCCESS);
}
