/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 04:51:25 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:02:36 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	atoi_exit(const char *str, long long *result)
{
	int					i;
	int					j;
	int					neg;
	unsigned long long	tmp_result;

	i = 0;
	while (is_blank(str[i]))
		i++;
	neg = str[i] == '-';
	i += (str[i] == '-' || str[i] == '+');
	tmp_result = 0;
	j = 0;
	while (str[i] && j++ < 19)
	{
		if (str[i] < '0' || str[i] > '9')
			return (FAILURE);
		tmp_result *= 10;
		tmp_result += str[i] - '0';
		i++;
	}
	if (str[i] || (!neg && tmp_result > 9223372036854775807U)
			|| (neg && tmp_result > 9223372036854775808U))
		return (FAILURE);
	*result = neg ? tmp_result * -1 : tmp_result;
	return (SUCCESS);
}

int			builtin_exit(t_command *command, t_mini *mini)
{
	long long	arg;
	int			exit_code;

	if (mini->exit_stop)
		return (SUCCESS);
	ft_putstr_fd("exit\n", 2);
	if (command->argc > 2)
	{
		put_error_msg(ERROR_EXIT_NB_ARGS, "exit", NULL);
		return (FAILURE);
	}
	if (command->argv[1])
	{
		if (SUCCESS != atoi_exit(command->argv[1], &arg))
		{
			put_error_msg(ERROR_EXIT_NUM_ARG, "exit", command->argv[1]);
			exit_code = (unsigned char)ERROR_SYNTAX;
		}
		else
			exit_code = arg;
	}
	else
		exit_code = mini->lst_status;
	quit(exit_code, mini);
	return (SUCCESS);
}
