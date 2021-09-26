/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 05:31:47 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:42:42 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t		i;

	if (!dest || !src)
		return (0);
	if (dstsize > 0)
	{
		i = 0;
		while (src[i] && i + 1 < dstsize)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
