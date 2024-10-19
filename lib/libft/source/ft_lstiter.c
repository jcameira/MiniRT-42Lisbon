/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/19 01:13:09 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.
Iterates the list 'lst' and applies
the function 'f' on the content of each node.
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !lst)
		return ;
	current = lst;
	while (current)
	{
		next = current->next;
		f(current->content);
		current = next;
	}
}
