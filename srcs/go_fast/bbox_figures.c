/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_figures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:20:02 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/13 16:50:44 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	sphere_bbox(t_figure *new_f)
{
	t_vec3	radius;
	float	min[3];
	float	max[3];
	// float	extent;
 	// float	world_size;
	// int		i;

	// i = -1;
	radius = (t_vec3){{new_f->f.sp.r, new_f->f.sp.r, new_f->f.sp.r}};
	vec3_subf(min, new_f->f.sp.c, radius.vec);
	vec3_addf(max, new_f->f.sp.c, radius.vec);
	init_bbox(&new_f->b, min, max);

	// while (++i < 3)
	// {
	// 	extent = fmaxf(fabsf(min[i]), fabsf(max[i]));
	// 	world_size = fmaxf(world_size, extent);
	// }
	// i = -1;
	// while (++i < 3)
	// {
	// 	new_f->b.x[i] = min[i] / world_size;
	// 	new_f->b.x[i] = max[i] / world_size;
	// 	new_f->b.y[i] = min[i] / world_size;
	// 	new_f->b.y[i] = max[i] / world_size;
	// 	new_f->b.z[i] = min[i] / world_size;
	// 	new_f->b.z[i] = max[i] / world_size;
	// }
	return ;
}
