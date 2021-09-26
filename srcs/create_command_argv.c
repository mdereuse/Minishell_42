/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 04:54:57 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/09 13:22:16 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_command_args(char *str)
{
	int		i;
	int		argc;

	i = 0;
	argc = 0;
	while (str[i])
	{
		if (is_new_arg(str, i))
			argc++;
		i++;
	}
	return (argc);
}

static char	*create_new_arg(char *str)
{
	int		i;
	int		size;
	char	*arg;

	size = 0;
	while (str[size]
			&& (!is_white_space(str[size]) || inside_quote(str, size)))
		size++;
	if (!(arg = (char*)malloc(sizeof(*arg) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		arg[i] = str[i];
		i++;
	}
	arg[i] = '\0';
	return (arg);
}

char		**create_new_command_argv(char *str)
{
	int		i;
	int		j;
	char	**argv;

	if (!(argv = (char**)malloc(sizeof(*argv) * (count_command_args(str) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_new_arg(str, i))
		{
			if (!(argv[j] = create_new_arg(str + i)))
			{
				ft_clean_tab_index(argv, j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	argv[j] = NULL;
	return (argv);
}
