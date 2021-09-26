/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 16:27:06 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 20:45:28 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_last_and_previous_word(t_mini *mini)
{
	t_list		*current;
	t_command	*command;
	t_command	*nxt_command;
	char		*last_word;

	current = mini->com_list;
	while (current)
	{
		command = current->content;
		nxt_command = current->next ? current->next->content : NULL;
		last_word = ft_tablast(command->argv);
		if (last_word
				&& (!(command->last_word = ft_strdup(last_word))
					|| (nxt_command
						&& !(nxt_command->previous_word =
							ft_strdup(last_word)))))
			return (ENOMEM);
		current = current->next;
	}
	return (SUCCESS);
}

int			parse_line(char *line, t_mini *mini)
{
	int		i;
	int		ret;

	i = 0;
	while (line[i])
	{
		if (is_new_command(line, i))
			if (SUCCESS != (ret = add_new_command(line + i, mini)))
				return (ret);
		i++;
	}
	return (set_last_and_previous_word(mini));
}
