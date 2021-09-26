/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 05:46:07 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:43:00 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_strnlen(const char *s, size_t max)
{
	size_t		i;

	i = 0;
	while (s[i] && i < max)
		i++;
	return (i);
}

size_t				ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = ft_strnlen(dest, dstsize);
	j = ft_strlen(src);
	j += i;
	k = 0;
	while (src[k] && i + 1 < dstsize)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	if (i < dstsize)
		dest[i] = '\0';
	return (j);
}
