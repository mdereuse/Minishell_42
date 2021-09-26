/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 08:59:15 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 05:55:23 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	number;
	char	c;

	number = (long)n;
	if (number < 0)
	{
		write(fd, "-", 1);
		number *= -1;
	}
	if (number / 10)
		ft_putnbr_fd(number / 10, fd);
	c = number % 10 + '0';
	write(fd, &c, 1);
}
