/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_and_oldpwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 18:08:20 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:42:24 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extend_path(char *old_path, char *new_dir)
{
	char	*tmp_path;
	char	*new_path;

	if (!(tmp_path = ft_strjoin(old_path, "/")))
		return (NULL);
	new_path = ft_strjoin(tmp_path, new_dir);
	free(tmp_path);
	return (new_path);
}

static int	get_previous_pwd(char **pwd, char *path, t_mini *mini)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
	{
		put_error_msg(errno, "cd", "getcwd");
		if (!(*pwd = extend_path(mini->cwd, path)))
			return (ENOMEM);
	}
	else if (!(*pwd = ft_strdup(cwd)))
		return (ENOMEM);
	return (SUCCESS);
}

int			replace_old_pwd(t_mini *mini)
{
	int		ret;
	char	*oldpwd;

	oldpwd = NULL;
	if ((key_not_found("PWD", mini) || value_not_found("PWD", mini)))
	{
		if (mini->pwd && !(oldpwd = ft_strdup(mini->pwd)))
			return (ENOMEM);
	}
	else if (SUCCESS != (ret = get_dup_env_var_value(&oldpwd, "PWD", mini)))
		return (ret);
	if (mini->oldpwd)
		free(mini->oldpwd);
	if (key_not_found("OLDPWD", mini))
		mini->oldpwd = oldpwd;
	else
	{
		mini->oldpwd = NULL;
		if (SUCCESS != (ret = set_env_var_value("OLDPWD", oldpwd, mini)))
		{
			free(oldpwd);
			return (ret);
		}
	}
	return (SUCCESS);
}

int			replace_pwd(char *path, t_mini *mini)
{
	int		ret;
	char	*pwd;

	if (SUCCESS != (ret = get_previous_pwd(&pwd, path, mini)))
		return (ret);
	free(mini->cwd);
	if (!(mini->cwd = ft_strdup(pwd)))
		return (ENOMEM);
	if (mini->pwd)
		free(mini->pwd);
	if (key_not_found("PWD", mini))
		mini->pwd = pwd;
	else
	{
		mini->pwd = NULL;
		if (SUCCESS != (ret = set_env_var_value("PWD", pwd, mini)))
		{
			free(pwd);
			return (ret);
		}
	}
	return (SUCCESS);
}

int			restore_pwd_and_oldpwd(char *key, t_mini *mini)
{
	char	*value;
	int		ret;

	if ((!ft_strcmp(key, "PWD")
				&& !(value = ft_strdup(mini->pwd)))
			|| (!ft_strcmp(key, "OLDPWD")
				&& !(value = ft_strdup(mini->oldpwd))))
		return (ENOMEM);
	if (SUCCESS != (ret = set_env_var_value(key, value, mini)))
	{
		free(value);
		return (ret);
	}
	if (!ft_strcmp(key, "PWD"))
	{
		free(mini->pwd);
		mini->pwd = NULL;
	}
	if (!ft_strcmp(key, "OLDPWD"))
	{
		free(mini->oldpwd);
		mini->oldpwd = NULL;
	}
	return (SUCCESS);
}
