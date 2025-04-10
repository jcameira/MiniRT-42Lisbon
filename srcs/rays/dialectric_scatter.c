/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dialectric_scatter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/10 18:58:28 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray	dialetric_scatter(t_ray *in_r, t_hitrecord *hit)
{
	float	refracted[3];
	float	ri;

	hit->attenuation = color(1.0, 1.0, 1.0);
	if (hit->front_face)
		ri = 1.0 / hit->mat.ri;
	else
		ri = hit->mat.ri;
	vec3_normalizef(in_r->dir);
	refract(refracted, in_r->dir, hit->normal, ri);
	return (get_ray(hit->p, refracted));
}
