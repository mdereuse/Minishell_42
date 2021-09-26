/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 01:06:56 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:40:04 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n
			&& (i == 0
				|| ((unsigned char*)src)[i - 1] != (unsigned char)c))
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	if (i > 0 && ((unsigned char*)dest)[i - 1] == (unsigned char)c)
		return (dest + i);
	return ((void*)0);
}
