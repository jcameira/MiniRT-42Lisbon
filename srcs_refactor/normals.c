/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:39:48 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/18 06:46:03 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	normal_sp(t_list *obj, t_hitrecord *hit)
{
	vec3_subf(hit->normal, hit->p, object_content(obj)->sp.c);
	vec3_scalef(hit->normal, hit->normal, (1.0 / object_content(obj)->sp.r));
}
