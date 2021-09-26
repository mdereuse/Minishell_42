/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 08:06:30 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:52:00 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size_number(long n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	long	nmb;
	size_t	size;
	char	*number;
	size_t	limit;

	nmb = (long)n;
	size = get_size_number(nmb);
	if (!(number = (char*)malloc(sizeof(*number) * (size + 1))))
		return ((void*)0);
	if (nmb < 0)
	{
		limit = 1;
		number[0] = '-';
		nmb *= -1;
	}
	else
		limit = 0;
	number[size] = '\0';
	while (size-- > limit)
	{
		number[size] = nmb % 10 + '0';
		nmb /= 10;
	}
	return (number);
}
