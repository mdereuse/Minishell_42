/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:34:39 by mariedere         #+#    #+#             */
/*   Updated: 2020/04/10 07:34:52 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstat(t_list *lst, int index)
{
	int		i;
	t_list	*current;

	i = 0;
	current = lst;
	while (current && i < index)
	{
		current = current->next;
		i++;
	}
	if (i == index)
		return (current);
	return (NULL);
}
