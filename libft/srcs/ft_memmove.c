/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 02:19:44 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:40:33 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return ((void*)0);
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
			i++;
		}
	}
	else
	{
		while (n--)
			((unsigned char*)dest)[n] = ((unsigned char*)src)[n];
	}
	return (dest);
}
