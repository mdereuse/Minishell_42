/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:26:33 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:48:31 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_in_set(char c, const char *set)
{
	size_t		i;

	if (!set)
		return (-1);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int			get_size(const char *s1, const char *set)
{
	size_t		i;
	int			count;

	if (!s1 || !set)
		return (-1);
	i = 0;
	count = 0;
	while (s1[i] && is_in_set(s1[i], set))
	{
		count++;
		i++;
	}
	if (s1[i])
	{
		i = ft_strlen(s1) - 1;
		while (i >= 0 && is_in_set(s1[i], set))
		{
			count++;
			i--;
		}
	}
	return (ft_strlen(s1) - count);
}

char				*ft_strtrim(const char *s1, const char *set)
{
	char		*s2;
	int			size;
	int			i;
	int			j;

	if (!s1 || !set)
		return ((void*)0);
	size = get_size(s1, set);
	if (!(s2 = (char*)malloc(sizeof(*s2) * (size + 1))))
		return ((void*)0);
	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	j = 0;
	while (j < size)
	{
		s2[j] = s1[i + j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}
