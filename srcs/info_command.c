/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 23:39:49 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 17:00:30 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		is_entry_mode(t_redir_mode mode)
{
	return (mode == COMMAND_ENTRY
			|| mode == FILE_ENTRY);
}

bool		is_exit_mode(t_redir_mode mode)
{
	return (mode == COMMAND_EXIT
			|| mode == FILE_ER_EXIT
			|| mode == FILE_AP_EXIT);
}

bool		has_command_exit(t_command *command)
{
	return (command->last_word && !ft_strcmp(command->last_word, "|"));
}

bool		has_command_entry(t_command *command)
{
	return (command->previous_word && !ft_strcmp(command->previous_word, "|"));
}

bool		is_in_pipe_line(t_command *command)
{
	return (has_command_exit(command) || has_command_entry(command));
}
