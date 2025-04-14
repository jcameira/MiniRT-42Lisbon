/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .scatter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/14 08:50:01 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray	bump_scatter(t_ray *in_r, t_hitrecord *hit)
{
	(void)in_r;
	return (get_ray(hit->p, hit->normal));
}

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

void	reflect(float *result, float *v, float *n)
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

float	reflectance(float cosine, float ri)
{
	double	r0;

	r0 = (1.0 - ri) / (1.0 + ri);
	r0 = pow(r0, 2);
	return (r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0));
}

void	refract(float *result, float *v, float *n, float ri)
{
	float	v_tmp[3];
	float	r_out_perpendicular[3];
	float	r_out_parallel[3];
	float	cos_theta;
	float	sin_theta;

	vec3_scalef(v_tmp, v, -1.0);
	cos_theta = ft_fmin(vec3_dotf(v_tmp, n), 1.0);
	sin_theta = sqrt(1.0 - pow(cos_theta, 2));
	if ((ri * sin_theta) > 1.0 || reflectance(cos_theta, ri) > random_float())
	{
		reflect(result, v, n);
		return ;
	}
	vec3_scalef(r_out_perpendicular, n, cos_theta);
	vec3_addf(r_out_perpendicular, r_out_perpendicular, v);
	vec3_scalef(r_out_perpendicular, r_out_perpendicular, ri);
	vec3_scalef(r_out_parallel, n, -sqrt(fabs(1.0 - vec3_dotf(r_out_perpendicular, r_out_perpendicular))));
	vec3_addf(result, r_out_perpendicular, r_out_parallel);
}

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
