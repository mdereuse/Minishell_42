/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 06:22:07 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:09:23 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path_cd(char **path, t_command *command, t_mini *mini)
{
	int		ret;

	if (!command->argv[1]
			|| (command->argv[1] && !ft_strcmp(command->argv[1], "~")))
	{
		if (key_not_found("HOME", mini) || value_not_found("HOME", mini))
			return (ERROR_NO_HOME);
		if (SUCCESS != (ret = get_dup_env_var_value(path, "HOME", mini)))
			return (ret);
	}
	else if (!ft_strcmp(command->argv[1], "-"))
	{
		if (key_not_found("OLDPWD", mini) || value_not_found("OLDPWD", mini))
			return (ERROR_NO_OLDPWD);
		if (SUCCESS != (ret = get_dup_env_var_value(path, "OLDPWD", mini)))
			return (ret);
	}
	else
	{
		if (!(*path = ft_strdup(command->argv[1])))
			return (ENOMEM);
	}
	return (SUCCESS);
}

int			builtin_cd(t_command *command, t_mini *mini)
{
	char		*path;
	int			ret;

	if (SUCCESS != (ret = get_path_cd(&path, command, mini)))
	{
		put_error_msg(ret, "cd", NULL);
		return (FAILURE);
	}
	if (SUCCESS != chdir(path))
	{
		ret = errno;
		put_error_msg(ret, path, NULL);
		free(path);
		return (FAILURE);
	}
	if (SUCCESS != (ret = replace_old_pwd(mini))
			|| SUCCESS != (ret = replace_pwd(path, mini))
			|| SUCCESS != (ret = actualize_env_tab(mini)))
	{
		free(path);
		put_error_msg(ERROR_FTL, "cd", NULL);
		quit(EXIT_FAILURE, mini);
	}
	free(path);
	return (SUCCESS);
}
