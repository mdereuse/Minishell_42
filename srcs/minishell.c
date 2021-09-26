/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 16:17:41 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/21 08:09:22 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_line(char *line, t_mini *mini)
{
	int			ret;

	if (g_sigint_shell)
		mini->lst_status = 130;
	if (SUCCESS != (ret = parse_line(line, mini)))
	{
		free(line);
		ft_lstclear(&(mini->com_list), clean_command);
		mini->com_list = NULL;
		put_error_msg(ret, "line parsing", NULL);
		mini->lst_status = ret;
		return ;
	}
	free(line);
	if (!check_syntax_line_ok(mini))
	{
		put_error_msg(ERROR_SYNTAX, NULL, NULL);
		mini->lst_status = (unsigned char)ERROR_SYNTAX;
	}
	else
		launching_loop(mini);
	ft_lstclear(&(mini->com_list), clean_command);
	mini->com_list = NULL;
}

void		display_prompt(void)
{
	ft_putstr_fd("Minishell$ ", 2);
}

void		minishell(t_mini *mini)
{
	char	*line;
	int		ret;

	while (1)
	{
		g_sigint_shell = false;
		signal(SIGINT, sigint_handler_shell);
		signal(SIGQUIT, sigquit_handler_shell);
		display_prompt();
		line = NULL;
		if (FAILURE_GNL == (ret = get_next_line(0, &line)))
			put_error_msg(FAILURE_GNL, NULL, NULL);
		else if (EOF_GNL == ret)
		{
			free(line);
			ft_putstr_fd("exit\n", 2);
			quit(mini->lst_status, mini);
		}
		else
		{
			signal(SIGINT, sigint_handler_command);
			signal(SIGQUIT, sigquit_handler_command);
			manage_line(line, mini);
		}
	}
}
