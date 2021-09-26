/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 05:10:48 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/10 19:51:18 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

typedef struct			s_error
{
	int					code;
	char				*msg;
}						t_error;

const t_error			g_error_tab[] =
{
	{ERROR_SYNTAX, "Syntax error."},
	{ERROR_CMD_NOT_FOUND, "Command not found."},
	{FAILURE_GNL, "Wrong return from get_next_line."},
	{ERROR_NO_OLDPWD, "OLDPWD not set."},
	{ERROR_NO_HOME, "HOME not set."},
	{ERROR_KEY_NOT_FOUND, "Environment variable not found."},
	{ERROR_VALUE_NOT_FOUND, "Environment variable value not found."},
	{ERROR_EXIT_NB_ARGS, "Too many arguments."},
	{ERROR_EXIT_NUM_ARG, "Numeric argument only."},
	{ERROR_INVALID_KEY, "Invalid identifier."},
	{ERROR_FTL, "Fatal error : minishell must quit."},
	{0, NULL}
};

#endif
