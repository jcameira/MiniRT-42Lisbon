/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:12:41 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/02 15:47:49 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	hit_sp(t_ray *ray, float ray_max, t_hitrecord *hit_info, t_sphere sphere)
{
	float	oc[3];
	float	a;
	float	h;
	float	c;
	float	sqrtd;
	float	root;

	vec3_subf(oc, sphere.c, ray->o);
	a = vec3_dotf(ray->dir, ray->dir);
	h = vec3_dotf(ray->dir, oc);
	c = vec3_dotf(oc, oc) - (sphere.r * sphere.r);
	if ((h * h) - (a * c) < 0)
		return (0);
	sqrtd = sqrt((h * h) - (a * c));
	root = (h - sqrtd) / a;
	if (root <= 0.001 || root >= ray_max)
	{
		root = (h + sqrtd) / a;
		if (root <= 0.001 || root >= ray_max)
			return (0);
	}
	hit_info->t = root;
	vec3_scalef(ray->dir, ray->dir, root);
	vec3_addf(hit_info->p, ray->o, ray->dir);
	vec3_subf(hit_info->normal, hit_info->p, sphere.c);
	vec3_scalef(hit_info->normal, hit_info->normal, (1.0 / sphere.r));
	vec3_scalef(ray->dir, ray->dir, 1.0 / root);
	set_face_normal(ray->dir, hit_info);
	return (1);
}

int hit_pl(t_ray *ray, float ray_max, t_hitrecord *hit_info, t_plane plane)
{
	float	denominator;
	float	t;
	float	oc[3];

	denominator = vec3_dotf(plane.nv, ray->dir);
	if (fabs(denominator) <= 0.001)
		return (0);
	vec3_subf(oc, plane.p, ray->o);
	t = vec3_dotf(oc, plane.nv) / denominator;
	if (t <= 0.001 || t >= ray_max)
		return (0);
	hit_info->t = t;
	vec3_scalef(ray->dir, ray->dir, t);
	vec3_addf(hit_info->p, ray->o, ray->dir);
	vec3_scalef(ray->dir, ray->dir, 1.0 / t);
	vec3_copyf(hit_info->normal, plane.nv);
	set_face_normal(ray->dir, hit_info);
	return (1);
}

int	hit_cy(t_ray *ray, float ray_max, t_hitrecord *hit_info, t_cylinder cylinder)
{
	float	oc[3];
	float	c_base[3];
	float	a;
	float	h;
	float	c;
	float	m;
	float	sqrtd;
	float	root;

	vec3_scalef(c_base, cylinder.nv, -(cylinder.h / 2));
	vec3_addf(c_base, cylinder.c, c_base);
	vec3_subf(oc, c_base, ray->o);
	a = vec3_dotf(ray->dir, ray->dir) - pow(vec3_dotf(ray->dir, cylinder.nv), 2);
	h = vec3_dotf(ray->dir, oc) - (vec3_dotf(ray->dir, cylinder.nv) * vec3_dotf(oc, cylinder.nv));
	c = vec3_dotf(oc, oc) - pow(vec3_dotf(oc, cylinder.nv), 2) - pow(cylinder.r, 2);
	if ((h * h) - (a * c) < 0)
		return (0);
	sqrtd = sqrt((h * h) - (a * c));
	root = (h - sqrtd) / a;
	if (root <= 0.001 || root >= ray_max)
	{
		root = (h + sqrtd) / a;
		if (root <= 0.001 || root >= ray_max)
			return (0);
	}
	m = (vec3_dotf(ray->dir, cylinder.nv) * root) + vec3_dotf(oc, cylinder.nv);
	if (m < 0 || m > cylinder.h)
		return (0);
	hit_info->t = root;
	vec3_scalef(ray->dir, ray->dir, root);
	vec3_addf(hit_info->p, ray->o, ray->dir);
	vec3_scalef(ray->dir, ray->dir, 1.0 / root);
	vec3_scalef(hit_info->normal, cylinder.nv, m);
	vec3_addf(hit_info->normal, c_base, hit_info->normal);
	vec3_subf(hit_info->normal, hit_info->p, hit_info->normal);
	vec3_normalizef(hit_info->normal);
	set_face_normal(ray->dir, hit_info);
	return (1);
}

int	find_hittable(t_minirt *s, t_ray *ray, float ray_max, t_hitrecord *hit_info)
{
	t_figure	*tmp;
	float		closest;
	int			hit;

	closest = ray_max;
	hit = 0;
	tmp = s->scene.figures;
	while (tmp)
	{
		if ((tmp->type == SP && hit_sp(ray, closest, hit_info, tmp->f.sp))
			|| (tmp->type == PL && hit_pl(ray, closest, hit_info, tmp->f.pl))
			|| (tmp->type == CY && hit_cy(ray, closest, hit_info, tmp->f.cy)))
		{
			hit = 1;
			closest = hit_info->t;
			hit_info->attenuation = tmp->c;
		}
		tmp = tmp->next;
	}
	return (hit);
}
