/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/25 05:26:06 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray	lambertian_scatter(t_ray *in_r, t_hitrecord *hit)
{
	float	new_dir[3];

	(void)in_r;
	random_unit_vector(new_dir);
	vec3_addf(new_dir, hit->normal, new_dir);
	if (vec3_near_zerof(new_dir))
		vec3_copyf(new_dir, hit->normal);
	return (get_ray(hit->p, new_dir));
}

void	reflect(float *result,float *v, float *n)
{
	vec3_scalef(result, n, vec3_dotf(v, n));
	vec3_scalef(result, result, -2);
	vec3_addf(result, result, v);
}

t_ray	specular_scatter(t_ray *in_r, t_hitrecord *hit)
{
	float	reflected[3];
	float	random[3];

	reflect(reflected, in_r->dir, hit->normal);
	vec3_normalizef(reflected);
	random_unit_vector(random);
	vec3_scalef(random, random, hit->mat.fuzz);
	vec3_addf(reflected, reflected, random);
	return (get_ray(hit->p, reflected));
}
