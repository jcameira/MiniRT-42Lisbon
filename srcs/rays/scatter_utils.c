/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/10 19:03:20 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	reflect(float *result, float *v, float *n)
{
	vec3_scalef(result, n, vec3_dotf(v, n));
	vec3_scalef(result, result, -2);
	vec3_addf(result, result, v);
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
