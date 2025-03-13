/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:24:19 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/13 04:38:08 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


t_ray	get_ray(float origin[3], float direction[3])
{
	t_ray	ray;

	vec3_copyf(ray.o, origin);
	vec3_copyf(ray.dir, direction);
	return (ray);
}

void	set_face_normal(float ray_direction[3], t_hitrecord *hit_info)
{
	hit_info->front_face = vec3_dotf(ray_direction, hit_info->normal) < 0;
	if (!hit_info->front_face)
		vec3_scalef(hit_info->normal, hit_info->normal, -1);
}
