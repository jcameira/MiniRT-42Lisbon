/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:56:50 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 16:04:54 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	normal_co(t_list *obj, t_hitrecord *hit)
{
	float	normal[3];
	float	tmp[3];
	float	tip[3];
	float	cos_theta;
	float	m;

	vec3_scalef(tmp, object_content(obj)->co.nv, object_content(obj)->co.h);
	vec3_addf(tip, object_content(obj)->co.c, tmp);
	vec3_subf(tmp, hit->p, tip);
	cos_theta = object_content(obj)->co.h / \
		sqrt(pow(object_content(obj)->co.h, 2) + \
		pow(object_content(obj)->co.r, 2));
	m = vec3_dotf(tmp, object_content(obj)->co.nv);
	vec3_scalef(normal, object_content(obj)->co.nv, m * cos_theta);
	vec3_subf(normal, tmp, normal);
	vec3_normalizef(normal);
	vec3_copyf(hit->normal, normal);
	return (1);
}
