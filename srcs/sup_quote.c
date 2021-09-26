/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:46:14 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/06 21:53:06 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_unquoted_size(char *str)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (((str[i] != '\'' && str[i] != '\"')
					|| is_escaped(str, i)
					|| inside_quote(str, i))
				&& (str[i] != '\\'
					|| is_escaped(str, i)
					|| (inside_quote(str, i)
						&& !is_effective_antislash(str, i))))
			size++;
		i++;
	}
	return (size);
}

static char	*create_unquoted_word(char *old_word)
{
	int		i;
	int		j;
	int		size;
	char	*new_word;

	size = get_unquoted_size(old_word);
	if (!(new_word = (char*)malloc(sizeof(*new_word) * (size + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (old_word[i])
	{
		if (((old_word[i] != '\'' && old_word[i] != '\"')
					|| is_escaped(old_word, i)
					|| inside_quote(old_word, i))
				&& (old_word[i] != '\\'
					|| is_escaped(old_word, i)
					|| (inside_quote(old_word, i)
						&& !is_effective_antislash(old_word, i))))
			new_word[j++] = old_word[i++];
		else
			i++;
	}
	new_word[j] = '\0';
	return (new_word);
}

int			sup_quote_word(char **word)
{
	char	*tmp;

	tmp = *word;
	if (!(*word = create_unquoted_word(*word)))
	{
		*word = tmp;
		return (ENOMEM);
	}
	free(tmp);
	return (SUCCESS);
}

int			sup_quote_command(t_command *command)
{
	int		i;
	int		ret;

	i = 0;
	while (command->argv[i])
	{
		if (SUCCESS != (ret = sup_quote_word(&(command->argv[i]))))
			return (ret);
		i++;
	}
	return (SUCCESS);
}
