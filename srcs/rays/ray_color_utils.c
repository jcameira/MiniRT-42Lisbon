/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:19:07 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/24 16:34:11 by jcameira         ###   ########.fr       */
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


t_pixel	ray_color(t_minirt *s, t_ray ray, int depth)
{
	float		new_direction[3];
	float		ray_t[2];
	t_hitrecord	hit_info;
	t_pixel		final_color;

	if (depth <= 0)
		return (color(0, 0, 0));
	ray_t[min] = 0.001;
	ray_t[max] = INFINITY;
	if (!find_hittable(s, &ray, ray_t, &hit_info))
		return (color(0, 0, 0));
	random_on_hemisphere(new_direction, hit_info.normal);
	vec3_addf(new_direction, new_direction, hit_info.normal);
	if (vec3_near_zerof(new_direction))
		vec3_copyf(new_direction, hit_info.normal);
	t_pixel	color_emmited;
	if (hit_info.light)
		color_emmited = s->scene.lights->c;
	else
		color_emmited = color(0, 0, 0);
	t_pixel	color_scatter = attenuate_color(ray_color(s, get_ray(hit_info.p, new_direction), depth - 1), hit_info.attenuation);
	final_color.r = color_scatter.r + color_emmited.r;
	if (final_color.r > 255)
		final_color.r = 255;
	final_color.g = color_scatter.g + color_emmited.g;
	if (final_color.g > 255)
		final_color.g = 255;
	final_color.b = color_scatter.b + color_emmited.b;
	if (final_color.b > 255)
		final_color.b = 255;
	final_color.rgb = final_color.r << 16 | final_color.g << 8 | final_color.b;
	return (final_color);
}
