/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graveyard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:45:20 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/04 04:12:34 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//! unused
void	rgb_color(t_pixel *color, float surface_normal[3])
{
	color->r = 0.5 * ((surface_normal[0] + 1) * 256);
	color->g = 0.5 * ((surface_normal[1] + 1) * 256);
	color->b = 0.5 * ((surface_normal[2] + 1) * 256);
	color->rgb = color->r << 16 | color->g << 8 | color->b;
}

//! unused / deprecated
void get_real_color(t_pixel *real_p)
{
	real_p->r /= 10;
	real_p->g /= 10;
	real_p->b /= 10;
	real_p->rgb = real_p->r << 16 | real_p->g << 8 | real_p->b;
}

//! deprecated / new version
int	hit_sphere(t_ray *ray, float ray_max, t_hitrecord *hit_info, t_figure *tmp)
{
	float	oc[3];
	float	a;
	float	h;
	float	c;
	float	root;

	vec3_subf(oc, tmp->f.sp.c, ray->o);
	a = vec3_dotf(ray->dir, ray->dir);
	h = vec3_dotf(ray->dir, oc);
	c = vec3_dotf(oc, oc) -  (tmp->f.sp.r * tmp->f.sp.r);
	if ((h * h) - (a * c) < 0)
		return (0);
	root = (h - sqrt((h * h) - (a * c))) /  a;
	if (root <= 0.001 || root >= ray_max)
	{
		root = (h + sqrt((h * h) - (a * c))) /  a;
		if (root <= 0.001 || root >= ray_max)
			return (0);
	}
	hit_info->t = root;
	vec3_scalef(ray->dir, ray->dir, root);
	vec3_addf(hit_info->p, ray->o, ray->dir);
	vec3_subf(hit_info->normal, hit_info->p, tmp->f.sp.c);
	vec3_scalef(hit_info->normal, hit_info->normal, (1.0 / tmp->f.sp.r));
	vec3_scalef(ray->dir, ray->dir, 1.0 / root);
	set_face_normal(ray->dir, hit_info);
	return (1);
}
