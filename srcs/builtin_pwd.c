/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 04:24:21 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/03 11:30:34 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_pwd(t_command *command, t_mini *mini)
{
	ft_putstr_fd(mini->cwd, command->exit_fd);
	ft_putstr_fd("\n", command->exit_fd);
	return (SUCCESS);
}
