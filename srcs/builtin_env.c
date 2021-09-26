/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 04:17:39 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/20 00:16:18 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_env(t_command *command, t_mini *mini)
{
	int		i;

	(void)command;
	i = 0;
	while (mini->env_tab[i + 1])
	{
		ft_putstr_fd(mini->env_tab[i], command->exit_fd);
		ft_putstr_fd("\n", command->exit_fd);
		i++;
	}
	ft_putstr_fd("_=/usr/bin/env", command->exit_fd);
	ft_putstr_fd("\n", command->exit_fd);
	return (SUCCESS);
}
