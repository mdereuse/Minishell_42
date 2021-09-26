/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launching_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:09:24 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/21 12:09:19 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		launch_piped_commands(t_list *current, t_list *previous,
			t_mini *mini)
{
	t_command	*prv_command;
	int			ret;

	mini->exit_stop = true;
	prv_command = previous ? previous->content : NULL;
	if (SUCCESS != (ret = exec_command(current->content, prv_command, mini)))
	{
		put_error_msg(ret, "fatal error", NULL);
		quit(ret, mini);
	}
	previous = current;
	current = current->next;
	while (current && has_command_entry(current->content))
	{
		if (SUCCESS != (ret = exec_command(current->content, previous->content,
						mini)))
		{
			put_error_msg(ret, "fatal error", NULL);
			quit(ret, mini);
		}
		previous = current;
		current = current->next;
	}
	mini->exit_stop = false;
}

static void		launch_single_command(t_list *current, t_list *previous,
				t_mini *mini)
{
	t_command	*prv_command;
	int			ret;

	prv_command = previous ? previous->content : NULL;
	if (SUCCESS != (ret = exec_command(current->content, prv_command, mini)))
	{
		put_error_msg(ret, "fatal error", NULL);
		quit(ret, mini);
	}
}

static void		wait_processes(t_mini *mini)
{
	t_list		*current;
	t_process	*process;

	current = mini->process_list;
	while (current)
	{
		process = current->content;
		if (process->pid)
		{
			g_pid = process->pid;
			waitpid(process->pid, &(process->status), 0);
			if (process->status == 2)
				mini->lst_status = 130;
			else if (process->status == 131)
				mini->lst_status = process->status;
			else
				mini->lst_status = WEXITSTATUS(process->status);
			g_pid = 0;
		}
		else
			mini->lst_status = process->status;
		current = current->next;
	}
}

static void		launch(t_list *current, t_list *previous, t_mini *mini)
{
	if (has_command_exit(current->content))
		launch_piped_commands(current, previous, mini);
	else
		launch_single_command(current, previous, mini);
	wait_processes(mini);
	ft_lstclear(&(mini->process_list), free);
	mini->process_list = NULL;
	if (mini->lst_status == 131)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(SIGQUIT, 2);
		ft_putstr_fd("\n", 2);
	}
}

void			launching_loop(t_mini *mini)
{
	t_list		*current;
	t_list		*previous;

	current = mini->com_list;
	previous = NULL;
	g_sigint_command = false;
	while (current)
	{
		if (!has_command_entry(current->content))
		{
			if (g_sigint_command)
			{
				mini->lst_status = 130;
				break ;
			}
			launch(current, previous, mini);
		}
		previous = current;
		current = current->next;
	}
}
