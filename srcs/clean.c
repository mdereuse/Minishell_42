/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 01:20:18 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 17:14:37 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		close_clean(int *fd)
{
	int		ret;

	if (*fd == -1 || *fd == 0 || *fd == 1)
		return ;
	if ((ret = close(*fd)) < 0)
		put_error_msg(errno, "close", NULL);
	else
		*fd = -1;
}

void		clean_redir(void *content)
{
	t_redir		*redir;

	redir = content;
	if (redir->filename)
		free(redir->filename);
	close_clean(&(redir->fd));
	free(redir);
}

void		clean_command(void *content)
{
	t_command	*command;

	command = content;
	if (command->str)
		free(command->str);
	if (command->last_word)
		free(command->last_word);
	if (command->previous_word)
		free(command->previous_word);
	if (command->fst_arg)
		free(command->fst_arg);
	if (command->argv)
		ft_clean_tab(command->argv);
	ft_lstclear(&(command->redir_list), clean_redir);
	command->redir_list = NULL;
	close_clean(&(command->entry_fd));
	close_clean(&(command->exit_fd));
	free(command);
}

void		clean_env_var(void *content)
{
	t_env_var	*env_var;

	env_var = content;
	if (env_var->key)
		free(env_var->key);
	if (env_var->value)
		free(env_var->value);
	free(env_var);
}

void		clean_mini(t_mini *mini)
{
	ft_lstclear(&(mini->env_list), clean_env_var);
	ft_lstclear(&(mini->com_list), clean_command);
	ft_lstclear(&(mini->process_list), free);
	if (mini->env_tab)
		ft_clean_tab(mini->env_tab);
	if (mini->path)
		ft_clean_tab(mini->path);
	if (mini->pwd)
		free(mini->pwd);
	if (mini->oldpwd)
		free(mini->oldpwd);
	if (mini->cwd)
		free(mini->cwd);
	if (mini->lst_word)
		free(mini->lst_word);
	initialize_mini(mini);
}
