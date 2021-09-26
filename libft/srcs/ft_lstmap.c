/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 01:59:47 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/13 09:57:38 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*current_element;
	t_list		*new_list;
	t_list		*new_element;

	if (!lst)
		return ((void*)0);
	current_element = lst;
	new_list = (void*)0;
	while (current_element)
	{
		if (!(new_element = ft_lstnew((*f)(current_element->content))))
		{
			ft_lstclear(&new_list, del);
			return ((void*)0);
		}
		ft_lstadd_back(&new_list, new_element);
		current_element = current_element->next;
	}
	return (new_list);
}
