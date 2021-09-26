/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 06:09:00 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:02:11 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		is_absolute_path(char *path)
{
	return (path[0] && path[0] == '/');
}

bool		is_relative_path(char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

int			check_path_reg_file(char *path)
{
	t_stat	status;

	if (-1 == stat(path, &status))
		return (errno);
	if (S_ISDIR(status.st_mode))
		return (EISDIR);
	return (SUCCESS);
}
