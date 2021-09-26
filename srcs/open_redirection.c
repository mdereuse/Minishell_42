/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:14:04 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 17:58:41 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_redir *redir)
{
	if ((redir->mode == FILE_ER_EXIT
				&& -1 == (redir->fd = open(redir->filename,
					O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH)))
			|| (redir->mode == FILE_AP_EXIT
				&& -1 == (redir->fd = open(redir->filename,
					O_WRONLY | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH)))
			|| (redir->mode == FILE_ENTRY
				&& -1 == (redir->fd = open(redir->filename, O_RDONLY))))
		return (errno);
	return (SUCCESS);
}

static int	open_pipe_out(t_redir *redir, t_command *command)
{
	if (pipe(command->pipe_out))
		return (errno);
	redir->fd = command->pipe_out[1];
	return (SUCCESS);
}

static int	open_redirection(t_redir *redir, t_command *command,
			t_command *prv_command, t_mini *mini)
{
	int		ret;

	if (redir->mode == FILE_ER_EXIT || redir->mode == FILE_AP_EXIT
			|| redir->mode == FILE_ENTRY)
	{
		if (SUCCESS != (ret = open_file(redir)))
		{
			put_error_msg(ret, redir->filename, NULL);
			return (ret);
		}
	}
	else if (redir->mode == COMMAND_ENTRY && prv_command)
		redir->fd = prv_command->pipe_out[0];
	else if (redir->mode == COMMAND_EXIT)
	{
		if (SUCCESS != (ret = open_pipe_out(redir, command)))
		{
			put_error_msg(ret, "pipe", NULL);
			quit(ret, mini);
		}
	}
	return (SUCCESS);
}

static void	close_all_redirections(t_command *command)
{
	t_list	*current;
	t_redir	*redir;

	current = command->redir_list;
	while (current)
	{
		redir = current->content;
		close_clean(&(redir->fd));
		current = current->next;
	}
}

int			open_all_redirections(t_command *command, t_command *prv_command,
			t_mini *mini)
{
	t_list	*current;
	int		ret;

	current = command->redir_list;
	while (current)
	{
		if (SUCCESS != (ret = open_redirection(current->content, command,
						prv_command, mini)))
		{
			close_all_redirections(command);
			return (ret);
		}
		current = current->next;
	}
	return (SUCCESS);
}
