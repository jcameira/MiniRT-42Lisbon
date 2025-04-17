/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:47:05 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 05:39:08 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	set_hit_info(t_ray *ray, t_hitrecord *hit)
{
	if (hit->object)
	{
		vec3_scalef(hit->p, ray->dir, hit->t);
		vec3_addf(hit->p, ray->o, hit->p);
		if (!object_content(hit->object)->normal(hit->object, hit))
			return (0);
		set_face_normal(ray->dir, hit);
		if (object_content(hit->object)->uv)
			if (!object_content(hit->object)->uv(hit, hit->object))
				return (0);
		hit->mat = object_material(hit->object);
		hit->attenuation = hit->mat.get_color(hit->object, hit);
	}
	else
		return (0);
	return (1);
}

int	find_hittable(t_list *objects, t_ray *ray, t_hitrecord *hit)
{
	t_list	*tmp;
	float	t;

	hit->object = NULL;
	hit->t = INFINITY;
	tmp = objects;
	while (tmp)
	{
		t = object_content(tmp)->hit(tmp, ray, 0.001, hit->t);
		if (t > 0.0 && t < hit->t)
		{
			hit->object = tmp;
			hit->t = t;
		}
		tmp = tmp->next;
	}
	if (!set_hit_info(ray, hit))
		return (0);
	return (1);
}

t_pixel	ray_color(t_scene *scene, t_ray ray, int depth)
{
	t_hitrecord	hit;
	t_pixel		final_color;
	t_ray		new_ray;

	if (depth <= 0)
		return (color(0, 0, 0));
	if (!find_hittable(scene->objects, &ray, &hit))
		return (scale_pixel_color(scene->amb.al_c, scene->amb.al_br));
	if (object_content(hit.object)->mat.type == emission)
		return (scale_pixel_color(object_material(hit.object).c,
				object_material(hit.object).br));
	new_ray = hit.mat.scatter(&ray, &hit);
	final_color = ray_color(scene, new_ray, depth - 1);
	final_color = attenuate_color(hit.attenuation, final_color);
	return (final_color);
}
