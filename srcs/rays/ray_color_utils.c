/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:19:07 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/02 15:32:21 by jcameira         ###   ########.fr       */
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
	float		normalized_direction[3];
	float		new_direction[3];
	float		a;
	t_pixel		p_color;
	t_hitrecord	hit_info;

	if (depth <= 0)
		return (color(0, 0, 0));
	if (find_hittable(s, &ray, INFINITY, &hit_info))
	{
		random_on_hemisphere(new_direction, hit_info.normal);
		vec3_addf(new_direction, new_direction, hit_info.normal);
		if (fabs(new_direction[x]) < 1e-8 && fabs(new_direction[y]) < 1e-8 && fabs(new_direction[z]) < 1e-8)
			vec3_copyf(new_direction, hit_info.normal);
		return (attenuate_color(ray_color(s, get_ray(hit_info.p, new_direction), depth - 1), hit_info.attenuation));
	}
	vec3_copyf(normalized_direction, ray.dir);
	vec3_normalizef(normalized_direction);
	a = 0.5 * (normalized_direction[y] + 1);
	p_color.r = (1 - a) * 255 + a * 127;
	p_color.g = (1 - a) * 255 + a * 179;
	p_color.b = (1 - a) * 255 + a * 255;
	p_color.rgb = p_color.r << 16 | p_color.g << 8 | p_color.b;
	return (p_color);
}
