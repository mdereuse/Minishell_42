/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 05:13:48 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 17:17:43 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

static char		*get_error_msg(int error_code)
{
	int		i;

	if (error_code > 0
			&& error_code != ERROR_CMD_NOT_FOUND
			&& error_code != ERROR_SYNTAX)
		return (strerror(error_code));
	i = 0;
	while (g_error_tab[i].msg)
	{
		if (error_code == g_error_tab[i].code)
			return (g_error_tab[i].msg);
		i++;
	}
	return (NULL);
}

void			put_error_msg(int error_code, char *indic1, char *indic2)
{
	char	*msg;

	ft_putstr_fd("Minishell: ", 2);
	if (indic1)
	{
		ft_putstr_fd(indic1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (indic2)
	{
		ft_putstr_fd(indic2, 2);
		ft_putstr_fd(": ", 2);
	}
	if ((msg = get_error_msg(error_code)))
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
