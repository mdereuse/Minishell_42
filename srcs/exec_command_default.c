/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_default.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 17:26:21 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 17:32:19 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	while (pid == -1 && errno == EAGAIN)
		pid = fork();
	return (pid);
}

void		exec_command_default(t_command *command, int *status, pid_t *pid,
			t_mini *mini)
{
	int		ret;

	if (SUCCESS != (ret = set_fst_arg(command, mini)))
	{
		put_error_msg(ret, command->argv[0], NULL);
		if (ENOMEM == ret)
			quit(ret, mini);
		else if (ENOENT == ret)
			*status = ERROR_CMD_NOT_FOUND;
		else
			*status = ERROR_CMD_EXEC;
		return ;
	}
	if (-1 == (*pid = create_child_process()))
	{
		put_error_msg(ENOMEM, "fork", NULL);
		quit(ENOMEM, mini);
	}
	if (!*pid)
		child_process(command, mini);
}
