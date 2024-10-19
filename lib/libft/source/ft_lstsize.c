/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/19 01:13:35 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* Counts the number of nodes in a list.
Parameters
lst: The beginning of the list.
Return value: The length of the list */

int	ft_lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 1;
	while (lst-> next != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
