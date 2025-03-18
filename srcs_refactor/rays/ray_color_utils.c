/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:26:28 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/18 09:49:09 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	gamma_correction(t_pixel *color)
{
	color->r = 255 * sqrt((float)color->r / 255);
	color->g = 255 * sqrt((float)color->g / 255);
	color->b = 255 * sqrt((float)color->b / 255);
	color->rgb = color->r << 16 | color->g << 8 | color->b;
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
			//hit->attenuation = tmp->c;
			//hit->light = false;
		}
		tmp = tmp->next;
	}
	//if (hit_sp(ray, ray_t, hit, s->scene.lights->f.sp))
	//{
	//	hit = 1;
	//	ray_t[max] = hit->t;
	//	hit->attenuation = s->scene.lights->c;
	//	hit->light = true;
	//}
	if (hit->object)
	{
		vec3_scalef(hit->p, ray->dir, hit->t);
		vec3_addf(hit->p, ray->o, hit->p);
		object_content(hit->object)->normal(hit->object, hit);
		set_face_normal(ray->dir, hit);
	}
	else
		return (0);
	return (1);
}

t_pixel	ray_color(t_scene *scene, t_ray ray, int depth)
{
	t_hitrecord	hit;
	t_pixel		final_color;
	float		unit_direction[3];
	float		tmp;	

	if (depth <= 0)
		return (color(0,0,0));
	if (find_hittable(scene->objects, &ray, &hit))
	{
		random_unit_vector(unit_direction);
		vec3_addf(unit_direction, hit.normal, unit_direction);
		return (scale_pixel_color(ray_color(scene, get_ray(hit.p, unit_direction), depth - 1), 0.1));
	}
	vec3_copyf(unit_direction, ray.dir);
	vec3_normalizef(unit_direction);
	tmp = 0.5 * (unit_direction[y] + 1.0);
	final_color = scale_pixel_color(color(1.0, 1.0, 1.0), (1.0 - tmp));
	final_color = add_pixel_color(final_color, scale_pixel_color(color(0.5, 0.7, 1.0), tmp));
	return (final_color);
}
