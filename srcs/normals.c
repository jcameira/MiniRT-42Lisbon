/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:39:48 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 11:33:31 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	normal_sp(t_list *obj, t_hitrecord *hit)
{
	vec3_subf(hit->normal, hit->p, object_content(obj)->sp.c);
	vec3_scalef(hit->normal, hit->normal, (1.0 / object_content(obj)->sp.r));
}

void	normal_pl(t_list *obj, t_hitrecord *hit)
{
	vec3_copyf(hit->normal, object_content(obj)->pl.nv);
}

void	normal_qu(t_list *obj, t_hitrecord *hit)
{
	vec3_copyf(hit->normal, object_content(obj)->qu.nv);
}

void	normal_cy(t_list *obj, t_hitrecord *hit)
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
}
