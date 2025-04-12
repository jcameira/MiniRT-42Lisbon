/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:12:41 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 16:45:30 by jcameira         ###   ########.fr       */
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

float	hit_cy(t_list *obj, t_ray *ray, float min, float max)
{
	t_cylinder	content;
	float		abc[3];
	float		d;
	float		h[3];
	float		root;
	float		oc[3];

	content = object_content(obj)->cy;
	vec3_subf(oc, content.c, ray->o);
	abc[0] = vec3_dotf(ray->dir, ray->dir) - pow(vec3_dotf(ray->dir, content.nv), 2);
	abc[1] = vec3_dotf(ray->dir, oc) - (vec3_dotf(ray->dir, content.nv) * vec3_dotf(oc, content.nv));
	abc[2] = vec3_dotf(oc, oc) - pow(vec3_dotf(oc, content.nv), 2) - pow(content.r, 2);
	if ((abc[1] * abc[1]) - (abc[0] * abc[2]) < 0)
		return (-1.0);
	d = sqrt((abc[1] * abc[1]) - (abc[0] * abc[2]));
	root = (abc[1] - d) / abc[0];
	vec3_scalef(h, ray->dir, root);
	vec3_addf(h, h, ray->o);
	vec3_subf(h, h, content.c);
	if (root < min || root > max || fabs(vec3_dotf(h, content.nv)) > (content.h / 2.0))
	{
		root = (abc[1] + d) / abc[0];
		vec3_scalef(h, ray->dir, root);
		vec3_addf(h, h, ray->o);
		vec3_subf(h, h, content.c);
		if (root < min || root > max || fabs(vec3_dotf(h, content.nv)) > (content.h / 2.0))
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

//int hit_cy(t_ray *ray, float *ray_t, t_hitrecord *hit_info, t_cylinder cylinder)
//{
//	float	oc[3];
//	float	a, h, c;
//	float	root, sqrtd;
//
//	t_plane	bottom_cap;
//	t_plane	top_cap;
//	vec3_copyf(bottom_cap.nv, cylinder.nv);
//	vec3_scalef(bottom_cap.p, cylinder.nv, -1.0 * (cylinder.h / 2));
//	vec3_addf(bottom_cap.p, cylinder.c, bottom_cap.p);
//	vec3_copyf(top_cap.nv, cylinder.nv);
//	vec3_scalef(top_cap.p, cylinder.nv, cylinder.h / 2);
//	vec3_addf(top_cap.p, cylinder.c, top_cap.p);
//	t_hitrecord	cap_hit_info;
//	float		cap_hit_t = -1;
//	if (hit_pl(ray, ray_t, &cap_hit_info, bottom_cap))
//	{
//		float	distance_to_center[3];
//		vec3_subf(distance_to_center, cap_hit_info.p, bottom_cap.p);
//		if (vec3_lenf(distance_to_center) <= cylinder.r)
//		{
//			cap_hit_t = cap_hit_info.t;
//			*hit_info = cap_hit_info;
//		}
//	}
//	if (hit_pl(ray, ray_t, &cap_hit_info, top_cap))
//	{
//		float	distance_to_center[3];
//		vec3_subf(distance_to_center, cap_hit_info.p, top_cap.p);
//		if (vec3_lenf(distance_to_center) <= cylinder.r && (cap_hit_t < 0 || cap_hit_info.t < cap_hit_t))
//		{
//			cap_hit_t = cap_hit_info.t;
//			*hit_info = cap_hit_info;
//		}
//	}
//	vec3_subf(oc, cylinder.c, ray->o);
//	a = vec3_dotf(ray->dir, ray->dir) - pow(vec3_dotf(ray->dir, cylinder.nv), 2);
//	h = vec3_dotf(ray->dir, oc) - (vec3_dotf(ray->dir, cylinder.nv) * vec3_dotf(oc, cylinder.nv));
//	c = vec3_dotf(oc, oc) - pow(vec3_dotf(oc, cylinder.nv), 2) - pow(cylinder.r, 2);
//	if ((h * h) - (a * c) < 0)
//		return (0);
//	sqrtd = sqrt((h * h) - (a * c));
//	root = (h - sqrtd) / a;
//	if (root <= ray_t[min] || root >= ray_t[max])
//	{
//		root = (h + sqrtd) / a;
//		if (root <= ray_t[min] || root >= ray_t[max])
//			root = -1;
//	}
//	float	side_hit_t = -1;
//	float	hit_to_base[3], projection_length;
//	float	temp[3];
//	if (root > 0)
//	{
//		vec3_scalef(ray->dir, ray->dir, root);
//		vec3_addf(temp, ray->o, ray->dir);
//		vec3_scalef(ray->dir, ray->dir, 1.0 / root);
//		vec3_subf(hit_to_base, temp, cylinder.c);
//		projection_length = vec3_dotf(hit_to_base, cylinder.nv);
//		if (projection_length >= -(cylinder.h / 2) && projection_length <= cylinder.h / 2)
//		{
//			side_hit_t = root;
//			float	axis_projection[3];
//			vec3_scalef(axis_projection, cylinder.nv, projection_length);
//			vec3_subf(hit_info->normal, hit_to_base, axis_projection);
//			vec3_normalizef(hit_info->normal);
//		}
//	}
//	if (side_hit_t > 0 && (cap_hit_t < 0 || side_hit_t < cap_hit_t))
//	{
//		hit_info->t = side_hit_t;
//		vec3_copyf(hit_info->p, temp);
//		set_face_normal(ray->dir, hit_info);
//	}
//	else if (cap_hit_t > 0)
//		set_face_normal(ray->dir, hit_info);
//	else
//		return (0);
//	return (1);
//}

float	hit_qu(t_list *obj, t_ray *ray, float min, float max)
{
	t_quad	quad;
	float	denominator;
	float	t;
	float	intersection[3];
	float	local_hit[2];

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
	local_hit[0] = vec3_dotf(intersection, quad.u) / vec3_dotf(quad.u, quad.u);
	local_hit[1] = vec3_dotf(intersection, quad.v) / vec3_dotf(quad.v, quad.v);
	if (local_hit[0] < 0 || local_hit[0] > 1 || local_hit[1] < 0 || local_hit[1] > 1)
		return (-1.0);
	return (t);
}
