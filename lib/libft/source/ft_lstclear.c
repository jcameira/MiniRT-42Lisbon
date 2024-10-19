/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/19 01:13:04 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
lst: The address of a pointer to a node.
del: The address of the function used to delete the content of the node.
Deletes and frees the given node and every successor of that node,
using the function 'del' and free(3).
Finally, the pointer to the list must be set to NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !*lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		(del)((current)->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
