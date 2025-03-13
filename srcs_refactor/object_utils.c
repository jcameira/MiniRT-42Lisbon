/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:40:28 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/13 04:26:17 by jcameira         ###   ########.fr       */
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
