/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdereuse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:14:10 by mdereuse          #+#    #+#             */
/*   Updated: 2019/11/14 01:18:44 by mdereuse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_element;

	if (!(new_element = (t_list*)malloc(sizeof(*new_element))))
		return ((void*)0);
	new_element->content = content;
	new_element->next = (void*)0;
	return (new_element);
}
