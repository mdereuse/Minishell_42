/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 05:16:46 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 17:13:39 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_export(t_command *command, t_mini *mini)
{
	int		i;
	int		ret;

	if (!command->argv[1])
	{
		display_export(command, mini);
		return (SUCCESS);
	}
	i = 1;
	while (command->argv[i])
	{
		if (SUCCESS != (ret = manage_export_arg(command->argv[i], mini)))
		{
			if (ERROR_FTL == ret)
			{
				put_error_msg(ret, "export", NULL);
				quit(EXIT_FAILURE, mini);
			}
			put_error_msg(ret, "export", command->argv[i]);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
