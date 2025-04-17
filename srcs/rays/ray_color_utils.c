/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:26:28 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 05:38:26 by jcameira         ###   ########.fr       */
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

int	get_sphere_uv(t_hitrecord *hit, t_list *content)
{
	float	theta;
	float	phi;
	float	tmp[3];

	(void)content;
	vec3_copyf(tmp, hit->p);
	vec3_normalizef(tmp);
	theta = acosf(-tmp[y]);
	phi = atan2f(-tmp[z], tmp[x]) + M_PI;
	hit->u = phi / (2 * M_PI);
	hit->v = theta / M_PI;
	hit->tg[0] = -cosf(phi);
	hit->tg[1] = 0;
	hit->tg[2] = sinf(phi);
	hit->bitg[0] = sinf(theta) * sinf(phi);
	hit->bitg[1] = cosf(theta);
	hit->bitg[2] = sinf(theta) * cosf(phi);
	vec3_normalizef(hit->tg);
	vec3_normalizef(hit->bitg);
	return (1);
}

int	get_quad_uv(t_hitrecord *hit, t_list *content)
{
	t_quad	qu;
	float	ap[3];
	float	tg[3];
	float	bitg[3];

	qu = object_content(content)->qu;
	vec3_subf(ap, hit->p, qu._q);
	hit->u = vec3_dotf(ap, qu.u) / vec3_dotf(qu.u, qu.u);
	hit->v = vec3_dotf(ap, qu.v) / vec3_dotf(qu.v, qu.v);
	vec3_copyf(tg, qu.u);
	vec3_copyf(bitg, qu.v);
	vec3_normalizef(tg);
	vec3_normalizef(bitg);
	vec3_copyf(hit->tg, tg);
	vec3_copyf(hit->bitg, bitg);
	return (1);
}
