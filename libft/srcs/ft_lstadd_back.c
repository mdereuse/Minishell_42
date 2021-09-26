/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:49:58 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/07 17:19:32 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*current_element;

	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		current_element = *alst;
		while (current_element->next)
			current_element = current_element->next;
		current_element->next = new;
	}
}
