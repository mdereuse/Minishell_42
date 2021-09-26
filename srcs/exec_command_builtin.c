/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 17:19:42 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 17:29:33 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void		exec_command_builtin(t_command *command, int *status, t_mini *mini)
{
	int		i;

	i = 0;
	while (command->argv[0] && g_builtin_tab[i].name)
	{
		if (!ft_strcmp(command->argv[0], g_builtin_tab[i].name))
		{
			*status = (*((g_builtin_tab[i]).fct))(command, mini);
			return ;
		}
		i++;
	}
}
