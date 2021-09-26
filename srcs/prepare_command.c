/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 04:33:00 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 00:22:34 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_entry_exit_fd(t_command *command)
{
	t_list	*current;
	t_redir	*redir;

	current = command->redir_list;
	while (current)
	{
		redir = current->content;
		if (is_entry_mode(redir->mode))
		{
			close_clean(&(command->entry_fd));
			command->entry_fd = redir->fd;
		}
		else
		{
			close_clean(&(command->exit_fd));
			command->exit_fd = redir->fd;
		}
		redir->fd = -1;
		current = current->next;
	}
}

int			prepare_command(t_command *command, t_command *prv_command,
			t_mini *mini)
{
	int			ret;

	if (SUCCESS != (ret = set_redirection(command, mini))
			|| SUCCESS != (ret = epure_argv(command))
			|| SUCCESS != (ret = replace_variable_command(command, mini))
			|| SUCCESS != (ret = sup_quote_command(command))
			|| SUCCESS != (ret = actualize_lst_word(command, mini)))
	{
		put_error_msg(ret, "fatal error", NULL);
		quit(ret, mini);
	}
	if (SUCCESS != (ret = open_all_redirections(command, prv_command, mini)))
		return (FAILURE);
	set_entry_exit_fd(command);
	command->argc = 0;
	while (command->argv[command->argc])
		command->argc++;
	return (SUCCESS);
}
