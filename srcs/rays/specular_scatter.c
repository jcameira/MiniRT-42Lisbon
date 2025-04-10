/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 03:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/10 18:59:14 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
