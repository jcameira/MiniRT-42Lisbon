/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:12:41 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/18 06:48:59 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//int	hit_pl(t_ray *ray, float ray_max, t_hitrecord *hit_info, t_plane plane)
//int	hit_pl(t_ray *ray, float *ray_t, t_hitrecord *hit_info, t_plane plane)
//{
//	float	denominator;
//	float	t;
//	float	oc[3];
//
//	denominator = vec3_dotf(plane.nv, ray->dir);
//	//if (fabs(denominator) <= 0.001)
//	if (fabs(denominator) <= ray_t[min])
//		return (0);
//	vec3_subf(oc, plane.p, ray->o);
//	t = vec3_dotf(oc, plane.nv) / denominator;
//	//if (t <= 0.001 || t >= ray_max)
//	if (t <= ray_t[min] || t >= ray_t[max])
//		return (0);
//	hit_info->t = t;
//	vec3_scalef(ray->dir, ray->dir, t);
//	vec3_addf(hit_info->p, ray->o, ray->dir);
//	vec3_scalef(ray->dir, ray->dir, 1.0 / t);
//	vec3_copyf(hit_info->normal, plane.nv);
//	set_face_normal(ray->dir, hit_info);
//	return (1);
//}

//int	hit_sp(t_ray *ray, float ray_max, t_hitrecord *hit_info, t_sphere sphere)
//int	hit_sp(t_ray *ray, float *ray_t, t_hitrecord *hit_info, t_sphere sphere)
//{
//	float	oc[3];
//	float	a;
//	float	h;
//	float	c;
//	float	sqrtd;
//	float	root;
//
//	vec3_subf(oc, sphere.c, ray->o);
//	a = vec3_dotf(ray->dir, ray->dir);
//	h = vec3_dotf(ray->dir, oc);
//	c = vec3_dotf(oc, oc) - (sphere.r * sphere.r);
//	if ((h * h) - (a * c) < 0)
//		return (0);
//	sqrtd = sqrt((h * h) - (a * c));
//	root = (h - sqrtd) / a;
//	//if (root <= 0.001 || root >= ray_max)
//	if (root <= ray_t[min] || root >= ray_t[max])
//	{
//		root = (h + sqrtd) / a;
//		//if (root <= 0.001 || root >= ray_max)
//		if (root <= ray_t[min] || root >= ray_t[max])
//			return (0);
//	}
//	hit_info->t = root;
//	vec3_scalef(ray->dir, ray->dir, root);
//	vec3_addf(hit_info->p, ray->o, ray->dir);
//	vec3_subf(hit_info->normal, hit_info->p, sphere.c);
//	vec3_scalef(hit_info->normal, hit_info->normal, (1.0 / sphere.r));
//	vec3_scalef(ray->dir, ray->dir, 1.0 / root);
//	set_face_normal(ray->dir, hit_info);
//	return (1);
//}

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

//int	hit_qu(t_ray *ray, float *ray_t, t_hitrecord *hit_info, t_quad quad)
//{
//	t_plane		plane;
//	t_hitrecord	temp_hit;
//    float		planar_hit[3];
//	float		local_hit[2];
//	
//	vec3_copyf(plane.p, quad._q);
//	vec3_crossf(plane.nv, quad.u, quad.v);
//	vec3_normalizef(plane.nv);
//	if (!hit_pl(ray, ray_t, &temp_hit, plane))
//		return (0);
//	vec3_subf(planar_hit, temp_hit.p, quad._q);
//	local_hit[0] = vec3_dotf(planar_hit, quad.u) / vec3_dotf(quad.u, quad.u);
//	local_hit[1] = vec3_dotf(planar_hit, quad.v) / vec3_dotf(quad.v, quad.v);
//	if (local_hit[0] < 0 || local_hit[0] > 1 || local_hit[1] < 0 || local_hit[1] > 1)
//		return (0);
//	*hit_info = temp_hit;
//	set_face_normal(ray->dir, hit_info);
//	return (1);
//}

//int	find_hittable(t_minirt *s, t_ray *ray, float *ray_t, t_hitrecord *hit_info)
//{
//	t_figure	*tmp;
//	int			hit;
//
//	hit = 0;
//	tmp = s->scene.figures;
//	while (tmp)
//	{
//		if ((tmp->type == SP && hit_sp(ray, ray_t, hit_info, tmp->f.sp))
//			|| (tmp->type == PL && hit_pl(ray, ray_t, hit_info, tmp->f.pl))
//			|| (tmp->type == CY && hit_cy(ray, ray_t, hit_info, tmp->f.cy))
//			|| (tmp->type == QU && hit_qu(ray, ray_t, hit_info, tmp->f.qu)))
//		{
//			hit = 1;
//			ray_t[max] = hit_info->t;
//			hit_info->attenuation = tmp->c;
//			hit_info->light = false;
//		}
//		tmp = tmp->next;
//	}
//	if (hit_sp(ray, ray_t, hit_info, s->scene.lights->f.sp))
//	{
//		hit = 1;
//		ray_t[max] = hit_info->t;
//		hit_info->attenuation = s->scene.lights->c;
//		hit_info->light = true;
//	}
//	return (hit);
//}

//void	copy_bbox_intervals(float dest[3][2], t_bbox bbox)
//{
//	dest[x][min] = bbox.x_interval[min];
//	dest[x][max] = bbox.x_interval[max];
//	dest[y][min] = bbox.y_interval[min];
//	dest[y][max] = bbox.y_interval[max];
//	dest[z][min] = bbox.z_interval[min];
//	dest[z][max] = bbox.z_interval[max];
//}
//
//void	copy_interval(float *dest, float *src)
//{
//	dest[min] = src[min];
//	dest[max] = src[max];
//}
//
//int	hit_bbox(t_ray *ray, float *ray_t, t_bbox bbox)
//{
//	int		i;
//	float	temp[3][2];
//	float	t0;
//	float	t1;
//
//	copy_bbox_intervals(temp, bbox);
//	i = -1;
//	while (++i < z)
//	{
//		t0 = (temp[i][min] - ray->o[i]) / ray->dir[i];
//		t1 = (temp[i][max] - ray->o[i]) / ray->dir[i];
//		if (t0 < t1)
//		{
//			if (t0 > ray_t[min])
//				ray_t[min] = t0;
//			if (t1 < ray_t[max])
//				ray_t[max] = t1;
//		}
//		else
//		{
//			if (t1 > ray_t[min])
//				ray_t[min] = t1;
//			if (t0 < ray_t[max])
//				ray_t[max] = t0;
//		}
//		if (ray_t[max] <= ray_t[min])
//			return (0);
//	}
//	return (1);
//}

//int	find_obj_to_hit(t_ray *ray, float *ray_t, t_hitrecord *hit_info, t_bvh *bvh)
//{
//	if (bvh->type == SP || bvh->type == L_SP)
//		return (hit_sp(ray, ray_t, hit_info, ((t_figure *)bvh->figure)->f.sp));
//	else if (bvh->type == QU || bvh->type == L_QU)
//		return (hit_qu(ray, ray_t, hit_info, ((t_figure *)bvh->figure)->f.qu));
//	else if (bvh->type == PL)
//		return (hit_pl(ray, ray_t, hit_info, ((t_figure *)bvh->figure)->f.pl));
//	else if (bvh->type == CY)
//		return (hit_cy(ray, ray_t, hit_info, ((t_figure *)bvh->figure)->f.cy));
//	return (0);
//}
//
//int	hit_bvh(t_ray *ray, float *ray_t, t_hitrecord *hit_info, t_bvh *bvh)
//{
//	float	temp[2];
//	int		hit_left;
//	int		hit_right;
//
//	temp[min] = ray_t[min];
//	temp[max] = ray_t[max];
//	if (!bvh || !hit_bbox(ray, ray_t, bvh->b))
//		return (0);
//	//printf("Here\n");
//	if (!bvh->left && !bvh->right)
//	{
//		if (find_obj_to_hit(ray, ray_t, hit_info, bvh))
//		{
//			//printf("Element Type Hit -> %d\n", bvh->type);
//			ray_t[max] = hit_info->t;
//			hit_info->attenuation = ((t_figure *)bvh->figure)->c;
//			hit_info->light = bvh->is_light;
//			//if (bvh->type == L_SP)
//			//	printf("Is light -> %d\n", hit_info->light);
//			return (1);
//		}
//		return (0);
//	}
//	hit_left = hit_bvh(ray, ray_t, hit_info, bvh->left);
//	ray_t[min] = temp[min];
//	ray_t[max] = temp[max];
//	if (hit_left)
//		ray_t[max] = hit_info->t;
//	//ray_t[max] = INFINITY;
//	hit_right = hit_bvh(ray, ray_t, hit_info, bvh->right);
//	return (hit_left || hit_right);
//}

//int	find_hittable(t_minirt *s, t_ray *ray, float *ray_t, t_hitrecord *hit_info)
//{
//	t_figure	*tmp;
//	int			hit;
//
//	hit = 0;
//	tmp = s->scene.figures;
//	while (tmp)
//	{
//		if ((tmp->type == SP && hit_sp(ray, ray_t, hit_info, tmp->f.sp))
//			|| (tmp->type == PL && hit_pl(ray, ray_t, hit_info, tmp->f.pl))
//			|| (tmp->type == CY && hit_cy(ray, ray_t, hit_info, tmp->f.cy))
//			|| (tmp->type == QU && hit_qu(ray, ray_t, hit_info, tmp->f.qu)))
//		{
//			hit = 1;
//			ray_t[max] = hit_info->t;
//			hit_info->attenuation = tmp->c;
//			hit_info->light = false;
//		}
//		tmp = tmp->next;
//	}
//	if (hit_sp(ray, ray_t, hit_info, s->scene.lights->f.sp))
//	{
//		hit = 1;
//		ray_t[max] = hit_info->t;
//		hit_info->attenuation = s->scene.lights->c;
//		hit_info->light = true;
//	}
//	return (hit);
//}
