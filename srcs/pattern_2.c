/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 18:43:02 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/07 18:43:57 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		is_escapable_char(char c)
{
	return (c == '\\'
			|| c == '\"'
			|| c == '\''
			|| c == '$');
}

bool		is_effective_antislash(char *str, int index)
{
	return (str[index] == '\\'
			&& !inside_simple_quote(str, index)
			&& (index == 0 || !is_effective_antislash(str, index - 1))
			&& is_escapable_char(str[index + 1]));
}

bool		is_escaped(char *str, int index)
{
	return (index > 0
			&& is_escapable_char(str[index])
			&& is_effective_antislash(str, index - 1));
}

bool		inside_simple_quote(char *str, int index)
{
	int		i;
	bool	quote;
	bool	d_quote;

	i = 0;
	quote = false;
	d_quote = false;
	while (i < index)
	{
		if (str[i] == '\'' && !is_escaped(str, i) && !d_quote && !quote)
			quote = true;
		else if (str[i] == '\'' && !is_escaped(str, i) && quote)
			quote = false;
		else if (str[i] == '\"' && !is_escaped(str, i) && !quote && !d_quote)
			d_quote = true;
		else if (str[i] == '\"' && !is_escaped(str, i) && d_quote)
			d_quote = false;
		i++;
	}
	if (quote && str[i] == '\'' && !is_escaped(str, i))
		quote = false;
	if (d_quote && str[i] == '\"' && !is_escaped(str, i))
		d_quote = false;
	return (quote);
}

bool		inside_quote(char *str, int index)
{
	int		i;
	bool	quote;
	bool	d_quote;

	i = 0;
	quote = false;
	d_quote = false;
	while (i < index)
	{
		if (str[i] == '\'' && !is_escaped(str, i) && !d_quote && !quote)
			quote = true;
		else if (str[i] == '\'' && !is_escaped(str, i) && quote)
			quote = false;
		else if (str[i] == '\"' && !is_escaped(str, i) && !quote && !d_quote)
			d_quote = true;
		else if (str[i] == '\"' && !is_escaped(str, i) && d_quote)
			d_quote = false;
		i++;
	}
	if (quote && str[i] == '\'' && !is_escaped(str, i))
		quote = false;
	if (d_quote && str[i] == '\"' && !is_escaped(str, i))
		d_quote = false;
	return (quote || d_quote);
}
