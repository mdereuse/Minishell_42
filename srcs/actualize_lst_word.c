/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actualize_lst_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:54:54 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 16:53:56 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			actualize_lst_word(t_command *command, t_mini *mini)
{
	char	*lst_word;

	free(mini->lst_word);
	mini->lst_word = NULL;
	lst_word = ft_tablast(command->argv);
	if (is_in_pipe_line(command) || !lst_word)
	{
		if (!(mini->lst_word = ft_strdup("")))
			return (ENOMEM);
	}
	else
	{
		if (!(mini->lst_word = ft_strdup(lst_word)))
			return (ENOMEM);
	}
	return (SUCCESS);
}
