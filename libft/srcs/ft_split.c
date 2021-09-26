/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 07:46:56 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 06:13:09 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	size_t	i;
	int		count;

	if (!s)
		return (-1);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	clean(char **tab, size_t index)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	extract_word(char const *s, char c, char **tab, size_t index)
{
	size_t	i;
	char	*word;

	if (!s || !tab)
		return (-1);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(word = (char*)malloc(sizeof(*word) * (i + 1))))
	{
		clean(tab, index);
		return (-1);
	}
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	tab[index] = word;
	return (0);
}

char		**ft_split(char const *s, char c)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	**tab;

	if (!s)
		return ((void*)0);
	size = count_words(s, c);
	if (!(tab = (char**)malloc(sizeof(*tab) * (size + 1))))
		return ((void*)0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			if (-1 == extract_word(s + i, c, tab, j))
				return ((void*)0);
			j++;
		}
		i++;
	}
	tab[j] = (void*)0;
	return (tab);
}
