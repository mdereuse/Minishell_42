/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:21:19 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/29 09:45:34 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		brioche(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
}

void		moutarde(int sig)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putstr_fd("\n", 2);
}

int			father_process(pid_t pid, t_command *command)
{
	int		status;

	if (0 != command->entry_fd)
		close(command->entry_fd);
	if (1 != command->exit_fd)
		close(command->exit_fd);
	if (-1 == waitpid(pid, &status, 0))
	{
		put_error_msg(errno, "waitpid", NULL);
		return (FAILURE);
	}
	return (WEXITSTATUS(status));
}
