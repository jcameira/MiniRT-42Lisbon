/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:12:41 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 04:47:53 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	hit_pl(t_list *obj, t_ray *ray, float min, float max)
{
	t_plane	plane;
	float	denominator;
	float	t;
	float	oc[3];

	plane = object_content(obj)->pl;
	denominator = vec3_dotf(plane.nv, ray->dir);
	if (fabs(denominator) > EPSILON)
	{
		vec3_subf(oc, plane.p, ray->o);
		t = vec3_dotf(oc, plane.nv) / denominator;
		if (t > min && t < max)
			return (t);
	}
	return (-1.0);
}

float	hit_sp(t_list *obj, t_ray *ray, float min, float max)
{
	float		oc[3];
	float		h;
	float		c;
	float		d;
	float		root;

	vec3_subf(oc, object_content(obj)->sp.c, ray->o);
	h = vec3_dotf(ray->dir, oc);
	c = vec3_dotf(oc, oc) - pow(object_content(obj)->sp.r, 2);
	d = (h * h) - c;
	if (d < 0)
		return (-1.0);
	d = sqrt(d);
	root = (h - d);
	if (root <= min || root >= max)
	{
		root = (h + d);
		if (root <= min || root >= max)
			return (-1.0);
	}
	return (root);
}

float	hit_ds(t_list *obj, t_ray *ray, float min, float max)
{
	t_disk	content;
	float	d;
	float	t;
	float	oc[3];
	float	dist[3];

	content = object_content(obj)->ds;
	d = vec3_dotf(content.nv, ray->dir);
	if (fabs(d) > EPSILON)
	{
		vec3_subf(oc, content.c, ray->o);
		t = vec3_dotf(oc, content.nv) / d;
		vec3_scalef(dist, ray->dir, t);
		vec3_addf(dist, ray->o, dist);
		vec3_subf(dist, content.c, dist);
		if (t > min && t < max && vec3_lenf(dist) <= content.r)
			return (t);
	}
	return (-1.0);
}

float	hit_qu(t_list *obj, t_ray *ray, float min, float max)
{
	t_quad	quad;
	float	denominator;
	float	t;
	float	intersection[3];
	float	l_hit[2];

	quad = object_content(obj)->qu;
	vec3_crossf(quad.nv, quad.u, quad.v);
	vec3_normalizef(quad.nv);
	quad._d = vec3_dotf(quad.nv, quad._q);
	vec3_scalef(quad.w, quad.nv, 1.0 / vec3_dotf(quad.nv, quad.nv));
	denominator = vec3_dotf(quad.nv, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (-1.0);
	t = (quad._d - vec3_dotf(quad.nv, ray->o)) / denominator;
	if (t < min || t > max)
		return (-1.0);
	vec3_scalef(intersection, ray->dir, t);
	vec3_addf(intersection, ray->o, intersection);
	vec3_subf(intersection, intersection, quad._q);
	l_hit[0] = vec3_dotf(intersection, quad.u) / vec3_dotf(quad.u, quad.u);
	l_hit[1] = vec3_dotf(intersection, quad.v) / vec3_dotf(quad.v, quad.v);
	if (l_hit[0] < 0 || l_hit[0] > 1 || l_hit[1] < 0 || l_hit[1] > 1)
		return (-1.0);
	return (t);
}
