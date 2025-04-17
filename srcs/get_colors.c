/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:59:41 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 02:23:13 by jcameira         ###   ########.fr       */
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
	x = (int)(hit->u * tmp_obj->mat.tex.img_texture.width);
	y = (int)(hit->v * tmp_obj->mat.tex.img_texture.height);
	pixel = *(unsigned int *)(tmp_obj->mat.tex.img_texture.data
			+ (y * tmp_obj->mat.tex.img_texture.size_line + x * 4));
	new_color.r = pixel >> 16 & 0xFF;
	new_color.g = pixel >> 8 & 0xFF;
	new_color.b = pixel & 0xFF;
	new_color.rgb = new_color.r << 16 | new_color.g << 8 | new_color.b;
	return (new_color);
}

float	get_bump(t_list *obj, float u, float v)
{
	t_object		*tmp_obj;
	unsigned int	pixel;
	int				x;
	int				y;

	tmp_obj = object_content(obj);
	u = clampf(u, 0, 1);
	v = 1 - clampf(v, 0, 1);
	x = (int)(u * tmp_obj->mat.tex.bump_texture.width);
	y = (int)(v * tmp_obj->mat.tex.bump_texture.height);
	pixel = *(unsigned int *)(tmp_obj->mat.tex.bump_texture.data
			+ (y * tmp_obj->mat.tex.bump_texture.size_line + x * 4));
	return ((float)(pixel >> 16 & 0xFF) / 255.0);
}

t_pixel	bump_color(t_list *obj, t_hitrecord *hit)
{
	float	h_uv[2];
	float	bump_uv[2];
	float	tu[3];
	float	bv[3];
	float	perturbation[3];

	h_uv[0] = get_bump(obj, hit->u + 0.001, hit->v);
	h_uv[1] = get_bump(obj, hit->u, hit->v + 0.001);
	bump_uv[0] = h_uv[0] - get_bump(obj, hit->u, hit->v);
	bump_uv[1] = h_uv[1] - get_bump(obj, hit->u, hit->v);
	vec3_scalef(tu, hit->tg, bump_uv[0] * 50);
	vec3_scalef(bv, hit->bitg, bump_uv[1] * 50);
	vec3_addf(perturbation, tu, bv);
	vec3_addf(hit->normal, hit->normal, perturbation);
	vec3_normalizef(hit->normal);
	return (image_color(obj, hit));
}
