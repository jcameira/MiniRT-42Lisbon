/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:26:28 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 15:47:40 by jcameira         ###   ########.fr       */
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
