/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fst_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:21:50 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 01:35:53 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_try_path(char *arg, char *path)
{
	char	*tmp_try_path;
	char	*try_path;

	if (!(tmp_try_path = ft_strjoin(path, "/")))
		return (NULL);
	if (!(try_path = ft_strjoin(tmp_try_path, arg)))
	{
		free(tmp_try_path);
		return (NULL);
	}
	free(tmp_try_path);
	return (try_path);
}

static int	set_fst_arg_default(t_command *command)
{
	int		ret;

	if (SUCCESS == (ret = check_path_reg_file(command->argv[0]))
			&& !(command->fst_arg = ft_strdup(command->argv[0])))
		return (ENOMEM);
	return (ret);
}

static int	set_fst_arg_from_env_path(t_command *command, t_mini *mini)
{
	char	*try_path;
	int		i;

	i = 0;
	while (mini->path && mini->path[i])
	{
		if (!(try_path = get_try_path(command->argv[0], mini->path[i])))
			return (ENOMEM);
		if (SUCCESS == check_path_reg_file(try_path))
		{
			command->fst_arg = try_path;
			return (SUCCESS);
		}
		free(try_path);
		i++;
	}
	return (ENOENT);
}

int			set_fst_arg(t_command *command, t_mini *mini)
{
	if (is_absolute_path(command->argv[0])
			|| is_relative_path(command->argv[0]))
		return (set_fst_arg_default(command));
	return (set_fst_arg_from_env_path(command, mini));
}
