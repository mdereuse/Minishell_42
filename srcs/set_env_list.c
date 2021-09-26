/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <mdereuse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 08:56:37 by mdereuse          #+#    #+#             */
/*   Updated: 2020/05/27 08:56:54 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			set_env_list(t_mini *mini, char **env)
{
	int		i;
	int		ret;

	i = 0;
	while (env[i])
	{
		if (SUCCESS != (ret = add_new_env_var(env[i], mini)))
			return (ret);
		i++;
	}
	return (SUCCESS);
}
