/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 17:35:57 by mariedere         #+#    #+#             */
/*   Updated: 2020/04/28 17:55:43 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_sort(t_list **alst, t_list *new, int sort(void *, void *))
{
	t_list	*current;
	t_list	*previous;

	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		current = *alst;
		previous = NULL;
		while (current && sort(current->content, new->content) < 0)
		{
			previous = current;
			current = current->next;
		}
		new->next = current;
		if (!previous)
			*alst = new;
		else
			previous->next = new;
	}
}
