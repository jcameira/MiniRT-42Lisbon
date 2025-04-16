/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:37:06 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 16:53:44 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	get_cylinder_root(t_cylinder content, t_ray *ray, float interval[2],
	float abc[3])
{
	float	d;
	float	h[3];
	float	root;

	d = sqrt((abc[1] * abc[1]) - (abc[0] * abc[2]));
	root = (abc[1] - d) / abc[0];
	vec3_scalef(h, ray->dir, root);
	vec3_addf(h, h, ray->o);
	vec3_subf(h, h, content.c);
	if (root < min || root > max
		|| fabs(vec3_dotf(h, content.nv)) > (content.h / 2.0))
	{
		root = (abc[1] + d) / abc[0];
		vec3_scalef(h, ray->dir, root);
		vec3_addf(h, h, ray->o);
		vec3_subf(h, h, content.c);
		if (root < interval[0] || root > interval[1]
			|| fabs(vec3_dotf(h, content.nv)) > (content.h / 2.0))
			return (-1.0);
	}
	return (root);
}

float	hit_cy(t_list *obj, t_ray *ray, float min, float max)
{
	t_cylinder	content;
	float		interval[2];
	float		abc[3];
	float		oc[3];

	content = object_content(obj)->cy;
	vec3_subf(oc, content.c, ray->o);
	abc[0] = vec3_dotf(ray->dir, ray->dir)
		- pow(vec3_dotf(ray->dir, content.nv), 2);
	abc[1] = vec3_dotf(ray->dir, oc) - (vec3_dotf(ray->dir, content.nv)
			* vec3_dotf(oc, content.nv));
	abc[2] = vec3_dotf(oc, oc) - pow(vec3_dotf(oc, content.nv), 2)
		- pow(content.r, 2);
	if ((abc[1] * abc[1]) - (abc[0] * abc[2]) < 0)
		return (-1.0);
	interval[0] = min;
	interval[1] = max;
	return (get_cylinder_root(content, ray, interval, abc));
}
