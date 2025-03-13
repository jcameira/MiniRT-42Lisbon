/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_figures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:20:02 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/02/18 02:53:20 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//void	sphere_bbox(t_figure *new_f)
//{
//	t_vec3	radius;
//	float	min[3];
//	float	max[3];
//	// float	extent;
// 	// float	world_size;
//	// int		i;
//
//	// i = -1;
//	radius = (t_vec3){{new_f->f.sp.r, new_f->f.sp.r, new_f->f.sp.r}};
//	vec3_subf(min, new_f->f.sp.c, radius.vec);
//	vec3_addf(max, new_f->f.sp.c, radius.vec);
//	init_bbox(&new_f->b, min, max);
//
//	// while (++i < 3)
//	// {
//	// 	extent = fmaxf(fabsf(min[i]), fabsf(max[i]));
//	// 	world_size = fmaxf(world_size, extent);
//	// }
//	// i = -1;
//	// while (++i < 3)
//	// {
//	// 	new_f->b.x[i] = min[i] / world_size;
//	// 	new_f->b.x[i] = max[i] / world_size;
//	// 	new_f->b.y[i] = min[i] / world_size;
//	// 	new_f->b.y[i] = max[i] / world_size;
//	// 	new_f->b.z[i] = min[i] / world_size;
//	// 	new_f->b.z[i] = max[i] / world_size;
//	// }
//	return ;
//}

void	sphere_bbox(t_figure *new_f)
{
	new_f->b.x_interval[min] = new_f->f.sp.c[x] - new_f->f.sp.r;
	new_f->b.x_interval[max] = new_f->f.sp.c[x] + new_f->f.sp.r;
	//printf("X_interval -> min: %f max: %f\n", new_f->b.x_interval[min], new_f->b.x_interval[max]);
	new_f->b.y_interval[min] = new_f->f.sp.c[y] - new_f->f.sp.r;
	new_f->b.y_interval[max] = new_f->f.sp.c[y] + new_f->f.sp.r;
	//printf("Y_interval -> min: %f max: %f\n", new_f->b.y_interval[min], new_f->b.y_interval[max]);
	new_f->b.z_interval[min] = new_f->f.sp.c[z] - new_f->f.sp.r;
	new_f->b.z_interval[max] = new_f->f.sp.c[z] + new_f->f.sp.r;
	//printf("Z_interval -> min: %f max: %f\n", new_f->b.z_interval[min], new_f->b.z_interval[max]);
}

int	hit_bbox(t_ray *ray, float *ray_t, t_bbox bbox)
{
	float	temp[3][2];
	float	tmp;
	float	t0;
	float	t1;
	int		i;

	vec2_copyf(temp[x], bbox.x_interval);
	vec2_copyf(temp[y], bbox.y_interval);
	vec2_copyf(temp[z], bbox.z_interval);
	i = -1;
	while (++i < 3)
	{
		tmp = 1.0f / ray->dir[i];
		t0 = (temp[i][min] - ray->o[i]) * tmp;
		t1 = (temp[i][max] - ray->o[i]) * tmp;
		if (t0 < t1)
		{
			if (t0 > ray_t[min])
				ray_t[min] = t0;
			if (t1 < ray_t[max])
				ray_t[max] = t1;
		}
		else
		{
			if (t1 > ray_t[min])
				ray_t[min] = t1;
			if (t0 < ray_t[max])
				ray_t[max] = t0;
		}
		if (ray_t[max] <= ray_t[min])
			return (0);
	}
	return (1);
}
