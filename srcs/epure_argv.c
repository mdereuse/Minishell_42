/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epure_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 11:09:21 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 21:45:53 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		sup_end_command(t_command *command)
{
	int			i;
	char		**tmp;

	i = 0;
	while (command->argv[i])
	{
		if (!ft_strcmp(command->argv[i], ";")
			|| !ft_strcmp(command->argv[i], "|"))
		{
			tmp = command->argv;
			if (!(command->argv = ft_rm_from_tab(command->argv, i)))
			{
				command->argv = tmp;
				return (ENOMEM);
			}
			free(tmp[i]);
			free(tmp);
			return (SUCCESS);
		}
		i++;
	}
	return (SUCCESS);
}

static int		sup_redirection_path(t_command *command)
{
	int		i;
	char	**tmp;

	i = 0;
	while (command->argv[i])
	{
		if (!ft_strcmp(command->argv[i], ">")
			|| !ft_strcmp(command->argv[i], ">>")
			|| !ft_strcmp(command->argv[i], "<"))
		{
			if (command->argv[i + 1])
			{
				tmp = command->argv;
				if (!(command->argv = ft_rm_from_tab(command->argv, i + 1)))
				{
					command->argv = tmp;
					return (ENOMEM);
				}
				free(tmp[i + 1]);
				free(tmp);
			}
		}
		i++;
	}
	return (SUCCESS);
}

static int		sup_redirection_symbol(t_command *command)
{
	int		i;
	char	**tmp;

	i = 0;
	while (command->argv[i])
	{
		if (!ft_strcmp(command->argv[i], ">")
			|| !ft_strcmp(command->argv[i], ">>")
			|| !ft_strcmp(command->argv[i], "<"))
		{
			tmp = command->argv;
			if (!(command->argv = ft_rm_from_tab(command->argv, i)))
			{
				command->argv = tmp;
				return (ENOMEM);
			}
			free(tmp[i]);
			free(tmp);
		}
		else
			i++;
	}
	return (SUCCESS);
}

int				epure_argv(t_command *command)
{
	int		ret;

	if (SUCCESS != (ret = sup_end_command(command))
		|| SUCCESS != (ret = sup_redirection_path(command))
		|| SUCCESS != (ret = sup_redirection_symbol(command)))
		return (ret);
	return (SUCCESS);
}
