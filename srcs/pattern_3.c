/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 18:44:08 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:44:46 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		is_new_arg(char *str, int index)
{
	return (str[index]
			&& !inside_quote(str, index)
			&& !is_white_space(str[index])
			&& (index == 0
				|| (!inside_quote(str, index - 1)
					&& is_white_space(str[index - 1]))));
}

bool		is_new_command(char *str, int index)
{
	return (str[index]
			&& !inside_quote(str, index)
			&& (index == 0
				|| (!inside_quote(str, index - 1)
					&& (str[index - 1] == ';' || str[index - 1] == '|'))));
}

bool		is_end_command(char *str, int index)
{
	return (str[index]
			&& !inside_quote(str, index)
			&& (str[index] == '|' || str[index] == ';'));
}

bool		is_new_variable(char *str, int index)
{
	return (!is_escaped(str, index)
			&& !inside_simple_quote(str, index)
			&& str[index] == '$'
			&& str[index + 1]
			&& (ft_isalnum(str[index + 1])
				|| str[index + 1] == '?'
				|| str[index + 1] == '_'
				|| str[index + 1] == '\''
				|| (str[index + 1] == '\"' && !inside_quote(str, index))));
}

bool		is_end_variable(char *str, int index)
{
	return (str[index] == ' '
			|| str[index] == '='
			|| str[index] == '$'
			|| str[index] == '\''
			|| str[index] == '\"');
}
