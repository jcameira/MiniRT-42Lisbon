/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:58:44 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/12 09:59:49 by jcameira         ###   ########.fr       */
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

inline t_light	*light_content(t_list *is)
{
	return ((t_light *)is->content);
}