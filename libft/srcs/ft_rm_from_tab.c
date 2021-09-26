/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_from_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 06:47:27 by mariedere         #+#    #+#             */
/*   Updated: 2020/05/08 06:47:36 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_rm_from_tab(char **tab, int index)
{
	int		size;
	int		i;
	int		j;
	char	**new_tab;

	size = 0;
	while (tab[size])
		size++;
	if (index >= size)
		return (NULL);
	if (!(new_tab = (char**)malloc(sizeof(*new_tab) * (size))))
		return (NULL);
	i = 0;
	j = 0;
	while (i + 1 < size)
	{
		if (j == index)
			j++;
		new_tab[i++] = tab[j++];
	}
	new_tab[i] = NULL;
	return (new_tab);
}
