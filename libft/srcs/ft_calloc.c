/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 08:08:03 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:43:52 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*memory;
	size_t			i;

	if (!(memory = (unsigned char*)malloc(sizeof(*memory) * (count * size))))
		return ((void*)0);
	i = 0;
	while (i < count * size)
	{
		memory[i] = 0;
		i++;
	}
	return ((void*)memory);
}
