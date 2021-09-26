/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 05:55:43 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:45:18 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_blank(char c)
{
	return (c == '\t'
			|| c == '\n'
			|| c == '\v'
			|| c == '\f'
			|| c == '\r'
			|| c == ' ');
}

bool		is_white_space(char c)
{
	return (c == ' ');
}

bool		is_separator_pattern(char *str)
{
	return (!ft_strcmp(str, ";")
			|| !ft_strcmp(str, "|")
			|| !ft_strcmp(str, "||")
			|| !ft_strcmp(str, "&")
			|| !ft_strcmp(str, "&&"));
}

bool		is_redirection_pattern(char *str)
{
	return (!ft_strcmp(str, ">")
			|| !ft_strcmp(str, ">>")
			|| !ft_strcmp(str, "<")
			|| !ft_strcmp(str, "<<"));
}

bool		is_special_pattern(char *str)
{
	return (is_redirection_pattern(str)
			|| is_separator_pattern(str));
}
