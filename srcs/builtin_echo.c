/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 05:01:31 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/04 06:28:35 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_echo(t_command *command, t_mini *mini)
{
	int		i;
	bool	new_line;

	(void)mini;
	if (!command->argv[1])
	{
		ft_putstr_fd("\n", command->exit_fd);
		return (SUCCESS);
	}
	new_line = ft_strcmp(command->argv[1], "-n");
	i = 1;
	while (command->argv[i] && !ft_strcmp(command->argv[i], "-n"))
		i++;
	while (command->argv[i])
	{
		ft_putstr_fd(command->argv[i], command->exit_fd);
		if (command->argv[i + 1])
			ft_putstr_fd(" ", command->exit_fd);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", command->exit_fd);
	return (SUCCESS);
}
