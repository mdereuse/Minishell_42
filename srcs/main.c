/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 20:37:01 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/21 12:17:04 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		initialize_mini(t_mini *mini)
{
	mini->env_tab = NULL;
	mini->env_list = NULL;
	mini->com_list = NULL;
	mini->process_list = NULL;
	mini->path = NULL;
	mini->pwd = NULL;
	mini->oldpwd = NULL;
	mini->cwd = NULL;
	mini->lst_word = NULL;
}

int			main(int argc, char **argv, char **env)
{
	t_mini		mini;
	int			ret;

	(void)argc;
	(void)argv;
	g_sigint_shell = false;
	g_sigint_command = false;
	g_pid = 0;
	initialize_mini(&mini);
	mini.lst_status = 0;
	mini.exit_stop = false;
	if (SUCCESS != (ret = set_env_list(&mini, env))
		|| SUCCESS != (ret = fix_pwd_oldpwd(&mini))
		|| SUCCESS != (ret = initialize_lst_word(&mini))
		|| SUCCESS != (ret = increment_shlvl(&mini))
		|| SUCCESS != (ret = set_env_tab(&mini))
		|| SUCCESS != (ret = set_path(&mini))
		|| SUCCESS != (ret = set_cwd(&mini)))
	{
		put_error_msg(ret, NULL, NULL);
		quit(EXIT_FAILURE, &mini);
	}
	minishell(&mini);
	clean_mini(&mini);
	return (0);
}
