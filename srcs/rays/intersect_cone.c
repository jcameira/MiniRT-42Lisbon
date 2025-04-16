/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:15:22 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 16:31:20 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	get_cone_root(t_cone content, t_ray *ray, float interval[2],
	float abc[3])
{
	float	d;
	float	m;
	float	h[3];
	float	root;

	d = sqrt((abc[1] * abc[1]) - (abc[0] * abc[2]));
	root = (-abc[1] - d) / abc[0];
	vec3_scalef(h, ray->dir, root);
	vec3_addf(h, h, ray->o);
	vec3_subf(h, h, content.c);
	m = vec3_dotf(h, content.nv);
	if (root < interval[0] || root > interval[1] || m < 0 || m > content.h)
	{
		root = (-abc[1] + d) / abc[0];
		vec3_scalef(h, ray->dir, root);
		vec3_addf(h, h, ray->o);
		vec3_subf(h, h, content.c);
		m = vec3_dotf(h, content.nv);
		if (root < interval[0] || root > interval[1] || m < 0 || m > content.h)
			return (-1.0);
	}
	return (root);
}

float	hit_co(t_list *obj, t_ray *ray, float min, float max)
{
	t_cone		content;
	float		abc[3];
	float		oc[3];
	float		interval[2];
	float		k;

	content = object_content(obj)->co;
	vec3_subf(oc, ray->o, content.c);
	k = (content.r / content.h);
	k = k * k;
	abc[0] = vec3_dotf(ray->dir, ray->dir) - (1 + k)
		* pow(vec3_dotf(ray->dir, content.nv), 2);
	abc[1] = vec3_dotf(ray->dir, oc) - (1 + k)
		* vec3_dotf(ray->dir, content.nv) * vec3_dotf(oc, content.nv);
	abc[2] = vec3_dotf(oc, oc) - (1 + k)
		* pow(vec3_dotf(oc, content.nv), 2);
	if ((abc[1] * abc[1]) - (abc[0] * abc[2]) < 0)
		return (-1.0);
	interval[0] = min;
	interval[1] = max;
	return (get_cone_root(content, ray, interval, abc));
}
