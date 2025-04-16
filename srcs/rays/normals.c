/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:39:48 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 15:56:39 by jcameira         ###   ########.fr       */
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
