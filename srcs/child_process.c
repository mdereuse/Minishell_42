/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 16:40:47 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/21 08:11:40 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		link_entry_exit(t_command *command)
{
	int		errnumber;

	if (0 != command->entry_fd
			&& -1 == dup2(command->entry_fd, STDIN_FILENO))
	{
		errnumber = errno;
		put_error_msg(errnumber, "dup2", NULL);
		return (errnumber);
	}
	if (1 != command->exit_fd
			&& -1 == dup2(command->exit_fd, STDOUT_FILENO))
	{
		errnumber = errno;
		put_error_msg(errnumber, "dup2", NULL);
		return (errnumber);
	}
	return (SUCCESS);
}

static void		child_sigint_handler(int sig)
{
	(void)sig;
	exit(130);
}

static void		child_sigquit_handler(int sig)
{
	(void)sig;
	exit(131);
}

void			child_process(t_command *command, t_mini *mini)
{
	int		ret;
	int		errnumber;

	if (SUCCESS != (ret = link_entry_exit(command)))
		quit(ret, mini);
	if (has_command_exit(command))
		close(command->pipe_out[0]);
	signal(SIGINT, child_sigint_handler);
	signal(SIGQUIT, child_sigquit_handler);
	execve(command->fst_arg, command->argv, mini->env_tab);
	errnumber = errno;
	put_error_msg(errnumber, command->fst_arg, NULL);
	if (ENOENT == errnumber)
		quit(ERROR_CMD_NOT_FOUND, mini);
	else
		quit(ERROR_CMD_EXEC, mini);
}
