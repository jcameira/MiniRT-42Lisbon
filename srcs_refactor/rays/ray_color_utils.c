/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:26:28 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/13 04:23:47 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pixel	ray_color(t_scene *scene, t_ray ray)
{
	t_hitrecord	hit;
	t_pixel		final_color;
	float		unit_direction[3];
	float		ray_t[2];
	float		tmp;	

	ray_t[min] = 0.001;
	ray_t[max] = INFINITY;
	if (hit_sp(&ray, ray_t, &hit, object_content(scene->objects)->sp) > 0.0)
	{
		vec3_copyf(unit_direction, hit.p);
		float	vec[3] = {0, 0, -1};
		vec3_subf(unit_direction, unit_direction, vec);
		vec3_normalizef(unit_direction);
		final_color = scale_pixel_color(color(unit_direction[x] + 1.0, unit_direction[y] + 1.0, unit_direction[z] + 1.0), 0.5);
		return (final_color);
	}
	vec3_copyf(unit_direction, ray.dir);
	vec3_normalizef(unit_direction);
	tmp = 0.5 * (unit_direction[y] + 1.0);
	final_color = scale_pixel_color(color(1.0, 1.0, 1.0), (1.0 - tmp));
	final_color = add_pixel_color(final_color, scale_pixel_color(color(0.5, 0.7, 1.0), tmp));
	return (final_color);
}
