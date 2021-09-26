/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_pwd_oldpwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <mdereuse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 05:47:54 by mdereuse          #+#    #+#             */
/*   Updated: 2020/06/20 06:06:58 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fix_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*arg;
	int		ret;

	if (!getcwd(cwd, PATH_MAX))
		return (errno);
	if (!(arg = ft_strjoin("PWD=", cwd)))
		return (ENOMEM);
	ret = export(arg, "PWD", mini);
	free(arg);
	return (ret);
}

static int	fix_oldpwd(t_mini *mini)
{
	return (export("OLDPWD", "OLDPWD", mini));
}

int			fix_pwd_oldpwd(t_mini *mini)
{
	int		ret;

	if (SUCCESS != (ret = fix_pwd(mini))
			|| SUCCESS != (ret = fix_oldpwd(mini)))
		return (ret);
	return (SUCCESS);
}
