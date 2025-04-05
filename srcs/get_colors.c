/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:59:41 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/05 05:35:30 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pixel	object_color(t_list *obj, t_hitrecord *hit)
{
	(void)hit;
	return (object_content(obj)->mat.c);
}

t_pixel	checkered_color(t_list *obj, t_hitrecord *hit)
{
	t_object	*content;
	float		inv_scale;

	content = object_content(obj);
	inv_scale = 1 / content->mat.tex.scale;
	if (((int)(hit->p[x] * inv_scale) + (int)(hit->p[y] * inv_scale)
		+ (int)(hit->p[z] * inv_scale)) % 2 == 0)
		return (content->mat.c);
	else
		return (content->mat.tex.checkered_c);
}
