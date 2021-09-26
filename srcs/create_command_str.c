/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 04:44:08 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/30 07:24:06 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	before_special_char(char *str, int index)
{
	return (!inside_quote(str, index)
			&& (((str[index] == '>'
						|| str[index] == '<'
						|| str[index] == '|'
						|| str[index] == '&')
					&& index > 0
					&& str[index - 1] != str[index])
				|| (str[index] == ';'
					&& index > 0)));
}

static bool	after_special_char(char *str, int index)
{
	return (!inside_quote(str, index)
			&& (((str[index] == '>'
						|| str[index] == '<'
						|| str[index] == '|'
						|| str[index] == '&')
					&& str[index + 1]
					&& str[index + 1] != str[index])
				|| (str[index] == ';'
					&& str[index + 1])));
}

static int	get_size_str_fmt(char *old_str)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (old_str[i])
	{
		if (before_special_char(old_str, i))
			size++;
		if (after_special_char(old_str, i))
			size++;
		size++;
		i++;
	}
	return (size);
}

static char	*create_new_command_str_fmt(char *old_str)
{
	char	*new_str;
	int		size;
	int		i;
	int		j;

	size = get_size_str_fmt(old_str);
	if (!(new_str = (char*)malloc(sizeof(*new_str) * (size + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (old_str[i])
	{
		if (before_special_char(old_str, i))
			new_str[j++] = ' ';
		new_str[j++] = old_str[i];
		if (after_special_char(old_str, i))
			new_str[j++] = ' ';
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char		*create_new_command_str(char *line)
{
	char	*str;
	char	*str_fmt;
	int		size;
	int		i;

	size = 0;
	while (line[size] && !is_end_command(line, size))
		size++;
	size++;
	if (!(str = (char*)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	if (!(str_fmt = create_new_command_str_fmt(str)))
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (str_fmt);
}
