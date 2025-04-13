/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:59:41 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 22:00:21 by cjoao-de         ###   ########.fr       */
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

t_pixel	image_color(t_list *obj, t_hitrecord *hit)
{
	t_object		*tmp_obj;
	t_pixel			new_color;
	unsigned int	pixel;
	int				x;
	int				y;

	tmp_obj = object_content(obj);
	hit->u = clampf(hit->u, 0, 1);
	hit->v = 1 - clampf(hit->v, 0, 1);
	//printf("U -> %f, V -> %f\n", hit->u, hit->v);
	x = (int)(hit->u * tmp_obj->mat.tex.texture.width);
	y = (int)(hit->v * tmp_obj->mat.tex.texture.height);
	pixel = *(unsigned int *)(tmp_obj->mat.tex.texture.data + (y * tmp_obj->mat.tex.texture.size_line + x * 4));
	new_color.r = pixel >> 16 & 0xFF;
	new_color.g = pixel >> 8 & 0xFF;
	new_color.b = pixel & 0xFF;
	new_color.rgb = new_color.r << 16 | new_color.g << 8 | new_color.b;
	//printf("Color -> %d\n", color.rgb);
	return (new_color);
}
