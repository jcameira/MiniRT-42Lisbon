/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:58:44 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 20:41:25 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_list	*new_light(void)
{
	t_light	*content;

	content = ft_calloc(1, sizeof(t_light));
	if (!content)
		return (NULL);
	return (ft_lstnew(content));
}

inline t_light	*light_content(t_list *object)
{
	return ((t_light *)object->content);
}
