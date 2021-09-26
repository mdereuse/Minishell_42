/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 18:44:54 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:45:27 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		is_end_key(char *str, int index)
{
	return (str[index] == '='
			|| (str[index + 1]
				&& str[index + 1] == '='
				&& str[index] == '+'));
}

bool		is_initialized(char *env_line)
{
	int		i;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

bool		is_modified(char *env_line)
{
	int		i;

	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (i > 0 && env_line[i - 1] == '+')
		return (true);
	return (false);
}
