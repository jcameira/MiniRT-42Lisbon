/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:26:28 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/05 05:50:35 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pixel	attenuate_color(t_pixel color, t_pixel attenuation)
{
	color.r *= (float)attenuation.r / 255;
	color.g *= (float)attenuation.g / 255;
	color.b *= (float)attenuation.b / 255;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}

void	gamma_correction(t_pixel *color)
{
	color->r = 255 * sqrt((float)color->r / 255);
	color->g = 255 * sqrt((float)color->g / 255);
	color->b = 255 * sqrt((float)color->b / 255);
	color->rgb = color->r << 16 | color->g << 8 | color->b;
}

void	get_sphere_uv(t_hitrecord *hit)
{
	float	theta;
	float	phi;

	theta = acosf(-hit->p[y]);
	phi = atan2f(-hit->p[z], hit->p[x]) + M_PI;
	hit->u = phi / (2 * M_PI);
	hit->v = theta / phi;
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
	if (hit->object)
	{
		vec3_scalef(hit->p, ray->dir, hit->t);
		vec3_addf(hit->p, ray->o, hit->p);
		object_content(hit->object)->normal(hit->object, hit);
		set_face_normal(ray->dir, hit);
		get_sphere_uv(hit);
		hit->mat = object_material(hit->object);
		hit->attenuation = hit->mat.get_color(hit->object, hit);
	}
	else
		return (0);
	return (1);
}

t_pixel	ray_color(t_scene *scene, t_ray ray, int depth)
{
	t_hitrecord	hit;
	t_pixel		final_color;
	//t_ray		new_ray;
	//float		unit_direction[3];
	//float		tmp;	

	if (depth <= 0)
		return (color(0,0,0));
	if (!find_hittable(scene->objects, &ray, &hit))
		//return (attenuate_color(ray_color(scene, hit.mat.scatter(&ray, &hit), depth - 1), hit.attenuation));
		return (color(0, 0, 0));
	if (object_content(hit.object)->mat.type == 4)
		return (scale_pixel_color(object_material(hit.object).c, object_material(hit.object).br));
	//new_ray = hit.mat.scatter(&ray, &hit);
	final_color = attenuate_color(ray_color(scene, hit.mat.scatter(&ray, &hit), depth - 1), hit.attenuation);
	return (final_color);
}
