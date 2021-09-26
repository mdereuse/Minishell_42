/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 03:09:49 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:45:06 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*new_str;

	if (!s)
		return ((void*)0);
	if (ft_strlen(s) < start)
		size = 0;
	else if ((ft_strlen(s) - start) < len)
		size = ft_strlen(s) - start;
	else
		size = len;
	if (!(new_str = (char*)malloc(sizeof(*new_str) * (size + 1))))
		return ((void*)0);
	i = 0;
	while (i < size)
	{
		new_str[i] = s[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
