/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 04:00:30 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:40:41 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char*)s)[i] == (unsigned char)c)
			return ((void*)(s + i));
		i++;
	}
	return ((void*)0);
}
