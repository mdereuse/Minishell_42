/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 09:04:51 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/30 13:45:57 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool		check_syntax_command_ok(t_command *command)
{
	int		i;

	if (command->argv[0]
			&& (is_separator_pattern(command->argv[0])))
		return (false);
	i = 0;
	while (command->argv[i])
	{
		if (is_redirection_pattern(command->argv[i])
				&& (!command->argv[i + 1]
					|| is_special_pattern(command->argv[i + 1])))
			return (false);
		i++;
	}
	return (true);
}

static bool		check_syntax_last_command_ok(t_command *command)
{
	return (!command->last_word || ft_strcmp(command->last_word, "|"));
}

bool			check_syntax_line_ok(t_mini *mini)
{
	t_list		*current;

	current = mini->com_list;
	while (current)
	{
		if (!check_syntax_command_ok(current->content))
			return (false);
		if (!current->next)
			return (check_syntax_last_command_ok(current->content));
		current = current->next;
	}
	return (true);
}
