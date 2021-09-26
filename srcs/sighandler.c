/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:21:25 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/21 08:04:27 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sigint_handler_shell(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	display_prompt();
	g_sigint_shell = true;
}

void		sigint_handler_command(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	if (g_pid)
		kill(g_pid, SIGINT);
	g_sigint_command = true;
}

void		sigquit_handler_shell(int sig)
{
	(void)sig;
	ft_putstr_fd("\e[2D\e[0K", 2);
}

void		sigquit_handler_command(int sig)
{
	(void)sig;
	if (g_pid)
		kill(g_pid, SIGQUIT);
}
