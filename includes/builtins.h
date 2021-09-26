/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 04:45:50 by mariedere         #+#    #+#             */
/*   Updated: 2020/04/15 13:03:08 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

typedef int				(*t_fct_builtin)(t_command*, t_mini*);

typedef struct			s_builtin
{
	char				*name;
	t_fct_builtin		fct;
}						t_builtin;

const t_builtin			g_builtin_tab[] =
{
	{"cd", &builtin_cd},
	{"echo", &builtin_echo},
	{"export", &builtin_export},
	{"env", &builtin_env},
	{"pwd", &builtin_pwd},
	{"exit", &builtin_exit},
	{"unset", &builtin_unset},
	{NULL, NULL}
};

#endif
