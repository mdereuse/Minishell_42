/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 05:57:02 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/31 16:45:37 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*create_new_command(char *line)
{
	t_command	*new_command;

	if (!(new_command = (t_command*)malloc(sizeof(*new_command))))
		return (NULL);
	new_command->str = NULL;
	new_command->previous_word = NULL;
	new_command->last_word = NULL;
	new_command->argv = NULL;
	new_command->fst_arg = NULL;
	new_command->redir_list = NULL;
	new_command->entry_fd = 0;
	new_command->exit_fd = 1;
	if (!(new_command->str = create_new_command_str(line)))
	{
		clean_command(new_command);
		return (NULL);
	}
	if (!(new_command->argv = create_new_command_argv(new_command->str)))
	{
		clean_command(new_command);
		return (NULL);
	}
	return (new_command);
}

int					add_new_command(char *line, t_mini *mini)
{
	t_command	*new_command;
	t_list		*new_element;

	if (!(new_command = create_new_command(line)))
		return (ENOMEM);
	if (!(new_element = ft_lstnew(new_command)))
	{
		clean_command(new_command);
		return (ENOMEM);
	}
	ft_lstadd_back(&(mini->com_list), new_element);
	return (SUCCESS);
}
