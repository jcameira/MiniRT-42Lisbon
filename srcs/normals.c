/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:39:48 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/14 06:43:24 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	normal_sp(t_list *obj, t_hitrecord *hit)
{
	vec3_subf(hit->normal, hit->p, object_content(obj)->sp.c);
	vec3_scalef(hit->normal, hit->normal, (1.0 / object_content(obj)->sp.r));
	return (1);
}

int	normal_pl(t_list *obj, t_hitrecord *hit)
{
	vec3_copyf(hit->normal, object_content(obj)->pl.nv);
	return (1);
}

int	normal_qu(t_list *obj, t_hitrecord *hit)
{
	vec3_copyf(hit->normal, object_content(obj)->qu.nv);
	return (1);
}

int	normal_ds(t_list *obj, t_hitrecord *hit)
{
	vec3_copyf(hit->normal, object_content(obj)->ds.nv);
	return (1);
}

int	normal_cy(t_list *obj, t_hitrecord *hit)
{
	float	normal[3];
	float	tmp[3];
	float	h;

	vec3_subf(tmp, hit->p, object_content(obj)->cy.c);
	h = vec3_dotf(tmp, object_content(obj)->cy.nv);
	vec3_scalef(normal, object_content(obj)->cy.nv, h);
	vec3_addf(normal, normal, object_content(obj)->cy.c);
	vec3_subf(normal, hit->p, normal);
	vec3_normalizef(normal);
	vec3_copyf(hit->normal, normal);
	return (1);
}

int	normal_co(t_list *obj, t_hitrecord *hit)
{
	float	normal[3];
	float	tmp[3];
	float	hit_to_tip[3];
	float	tip[3];
	float	cos_theta;
	float	m;
	
	// Step 1: Get cone tip position
	vec3_scalef(tmp, object_content(obj)->co.nv, object_content(obj)->co.h);
	vec3_addf(tip, object_content(obj)->co.c, tmp); // tip = base + axis * height
	
	// Step 2: Vector from tip to hit point
	vec3_subf(hit_to_tip, hit->p, tip);
	
	// Step 3: Compute surface angle (theta) via cos(θ) = h / sqrt(h^2 + r^2)
	cos_theta = object_content(obj)->co.h / sqrt(pow(object_content(obj)->co.h, 2) + pow(object_content(obj)->co.r, 2));
	
	// Step 4: Project onto axis to isolate surface direction
	m = vec3_dotf(hit_to_tip, object_content(obj)->co.nv);
	vec3_scalef(normal, object_content(obj)->co.nv, m * cos_theta);
	
	// Step 5: Subtract to get perpendicular surface vector
	vec3_subf(normal, hit_to_tip, normal);
	
	// Step 6: Normalize and assign
	vec3_normalizef(normal);
	vec3_copyf(hit->normal, normal);
	return (1);
}
