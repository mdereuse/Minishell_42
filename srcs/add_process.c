/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 17:16:28 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 17:17:04 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_process	*create_new_process(int status, pid_t pid)
{
	t_process	*new_process;

	if (!(new_process = (t_process*)malloc(sizeof(*new_process))))
		return (NULL);
	new_process->status = status;
	new_process->pid = pid;
	return (new_process);
}

int					add_new_process(int status, pid_t pid, t_mini *mini)
{
	t_process	*new_process;
	t_list		*new_element;

	if (!(new_process = create_new_process(status, pid)))
		return (ENOMEM);
	if (!(new_element = ft_lstnew(new_process)))
	{
		free(new_process);
		return (ENOMEM);
	}
	ft_lstadd_back(&(mini->process_list), new_element);
	return (SUCCESS);
}
