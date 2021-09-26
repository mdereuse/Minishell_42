/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 08:29:03 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:52:34 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t			size;
	unsigned int	i;
	char			*str;

	if (!s)
		return ((void*)0);
	size = ft_strlen(s);
	if (!(str = (char*)malloc(sizeof(*str) * (size + 1))))
		return ((void*)0);
	i = 0;
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
