/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian_scatter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/10 18:57:19 by cjoao-de         ###   ########.fr       */
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
