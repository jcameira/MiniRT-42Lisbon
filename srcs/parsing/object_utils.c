/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:40:28 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/11 14:47:15 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_list	*new_object(void)
{
	t_object	*content;

	content = ft_calloc(1, sizeof(t_object));
	if (!content)
		return (NULL);
	return (ft_lstnew(content));
}

inline t_object	*object_content(t_list *object)
{
	return ((t_object *)object->content);
}

inline t_material	object_material(t_list *object)
{
	return (object_content(object)->mat);
}

// inline t_pixel	figure_color(t_list *object)
// {
// 	return (object_content(object)->mat.c);
// }

inline t_ftype	object_type(t_list *object)
{
	return (object_content(object)->type);
}
