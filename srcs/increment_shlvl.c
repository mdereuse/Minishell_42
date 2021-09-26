/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:38:32 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/05 23:45:09 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	atoi_shlvl(const char *str)
{
	int		i;
	int		j;
	int		neg;
	int		result;

	i = 0;
	while (is_blank(str[i]))
		i++;
	neg = str[i] == '-';
	i += (str[i] == '-' || str[i] == '+');
	result = 0;
	j = 0;
	while (str[i] && j++ < 3)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		result = 10 * result + str[i] - '0';
		i++;
	}
	if (neg)
		return (-1);
	if (str[i] || result > 998)
		return (0);
	return (result);
}

int			increment_shlvl(t_mini *mini)
{
	int		shlvl;
	char	*value;
	char	*new_value;
	char	*arg;
	int		ret;

	if (value_not_found("SHLVL", mini))
		shlvl = 0;
	else
	{
		value = get_env_var_value("SHLVL", mini);
		shlvl = atoi_shlvl(value);
	}
	shlvl++;
	if (!(new_value = ft_itoa(shlvl)))
		return (ENOMEM);
	if (!(arg = ft_strjoin("SHLVL=", new_value)))
	{
		free(new_value);
		return (ENOMEM);
	}
	ret = export(arg, "SHLVL", mini);
	free(new_value);
	free(arg);
	return (ret);
}
