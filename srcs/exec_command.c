/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 03:36:01 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 17:51:27 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(char *arg)
{
	return (!ft_strcmp(arg, "echo")
			|| !ft_strcmp(arg, "cd")
			|| !ft_strcmp(arg, "pwd")
			|| !ft_strcmp(arg, "export")
			|| !ft_strcmp(arg, "unset")
			|| !ft_strcmp(arg, "env")
			|| !ft_strcmp(arg, "exit"));
}

int			exec_command(t_command *command, t_command *prv_command,
			t_mini *mini)
{
	int		ret;
	int		status;
	pid_t	pid;

	status = SUCCESS;
	pid = 0;
	if (SUCCESS != (ret = prepare_command(command, prv_command, mini)))
		status = FAILURE;
	else
	{
		if (!command->argv[0] || is_builtin(command->argv[0]))
			exec_command_builtin(command, &status, mini);
		else
			exec_command_default(command, &status, &pid, mini);
	}
	close_clean(&(command->entry_fd));
	close_clean(&(command->exit_fd));
	return (add_new_process(status, pid, mini));
}
