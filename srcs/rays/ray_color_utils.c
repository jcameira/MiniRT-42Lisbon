/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:26:28 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/14 10:10:46 by jcameira         ###   ########.fr       */
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
	hit->v = theta / M_PI;
	hit->tg[0] = -cos(phi);
	hit->tg[1] = 0;
	hit->tg[2] = sin(phi);
	hit->bitg[0] = sin(theta) * sin(phi);
	hit->bitg[1] = cos(theta);
	hit->bitg[2] = sin(theta) * cos(phi);
	vec3_normalizef(hit->tg);
	vec3_normalizef(hit->bitg);
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
		if (!object_content(hit->object)->normal(hit->object, hit))
			return (0);
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
	t_ray		new_ray;

	if (depth <= 0)
		return (color(0, 0, 0));
	if (!find_hittable(scene->objects, &ray, &hit))
		return (scale_pixel_color(scene->amb.al_c, scene->amb.al_br));
		//return (color(0, 0, 0));
	if (object_content(hit.object)->mat.type == emission)
		return (scale_pixel_color(object_material(hit.object).c, object_material(hit.object).br));
	new_ray = hit.mat.scatter(&ray, &hit);
	if (vec3_equal((vec3){0.0, 0.0, 0.0}, new_ray.dir))
		return (scale_pixel_color(scene->amb.al_c, scene->amb.al_br));
	final_color = ray_color(scene, new_ray, depth - 1);
	final_color = attenuate_color(final_color, hit.attenuation);
	//if (depth == 50)
	//	return (attenuate_color(final_color, scale_pixel_color(scene->amb.al_c, scene->amb.al_br)));
	return (final_color);
}
