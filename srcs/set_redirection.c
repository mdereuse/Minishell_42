/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:08:21 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 16:56:09 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_mode	get_redir_mode(char *indicator)
{
	if (!indicator)
		return (COMMAND_ENTRY);
	else if (!ft_strcmp(indicator, "<"))
		return (FILE_ENTRY);
	else if (!ft_strcmp(indicator, ">"))
		return (FILE_ER_EXIT);
	else if (!ft_strcmp(indicator, ">>"))
		return (FILE_AP_EXIT);
	else
		return (COMMAND_EXIT);
}

static t_redir		*create_new_redir(char *indicator, char *path, t_mini *mini)
{
	t_redir		*new_redir;

	if (!(new_redir = (t_redir*)malloc(sizeof(*new_redir))))
		return (NULL);
	new_redir->mode = get_redir_mode(indicator);
	new_redir->fd = -1;
	if (!path)
		new_redir->filename = NULL;
	else if (!(new_redir->filename = ft_strdup(path))
				|| (SUCCESS != replace_variable_word(&(new_redir->filename),
						mini))
				|| (SUCCESS != sup_quote_word(&(new_redir->filename))))
	{
		clean_redir(new_redir);
		return (NULL);
	}
	return (new_redir);
}

static int			add_new_redir(char *indicator, char *path,
					t_command *command, t_mini *mini)
{
	t_redir		*new_redir;
	t_list		*new_element;

	if (!(new_redir = create_new_redir(indicator, path, mini)))
		return (ENOMEM);
	if (!(new_element = ft_lstnew(new_redir)))
	{
		clean_redir(new_redir);
		return (ENOMEM);
	}
	if (new_redir->mode == COMMAND_ENTRY || new_redir->mode == COMMAND_EXIT)
		ft_lstadd_front(&(command->redir_list), new_element);
	else
		ft_lstadd_back(&(command->redir_list), new_element);
	return (SUCCESS);
}

int					set_redirection(t_command *command, t_mini *mini)
{
	int		i;
	int		ret;

	if (command->previous_word
		&& !ft_strcmp(command->previous_word, "|")
		&& SUCCESS != (ret =
				add_new_redir(NULL, NULL, command, mini)))
		return (ret);
	i = 0;
	while (command->argv[i])
	{
		if ((!ft_strcmp(command->argv[i], "<")
				|| !ft_strcmp(command->argv[i], ">")
				|| !ft_strcmp(command->argv[i], ">>")
				|| !ft_strcmp(command->argv[i], "|"))
			&& SUCCESS != (ret =
				add_new_redir(command->argv[i], command->argv[i + 1],
					command, mini)))
			return (ret);
		i++;
	}
	return (SUCCESS);
}
