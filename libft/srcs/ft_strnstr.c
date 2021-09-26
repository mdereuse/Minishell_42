/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 07:19:59 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:43:22 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *haystack, const char *needle,
				size_t len)
{
	size_t		i;
	size_t		j;

	if (!*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && i + ft_strlen(needle) <= len)
	{
		if (haystack[i] == *needle)
		{
			j = 0;
			while (needle[j] && needle[j] == haystack[i + j])
				j++;
			if (!needle[j])
				return ((char*)(haystack + i));
		}
		i++;
	}
	return ((void*)0);
}
