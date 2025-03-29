/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_oob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/14 19:17:00 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_coord project_normalized_vec3(const vec3 vec)
{
	t_coord pos;

	// Convert from [-1,1] to  [0,W-1] and [0,H-1]
	pos.pos[x] = (int)((vec[x] + 1.0f) * (W / 2));
	pos.pos[y] = (int)((1.0f - vec[y]) * (H / 2));

	// Clamp to viewport bounds
	pos.pos[x] = clamp(pos.pos[x], 0, W - 1);
	pos.pos[y] = clamp(pos.pos[y], 0, H - 1);
	pos.pos[z] = 0;
	// pos[x] = (pos[x] < 0) ? 0 : ((pos[x] >= W) ? W - 1 : pos[x]);
	// pos[y] = (pos[y] < 0) ? 0 : ((pos[y] >= H) ? H - 1 : pos[y]);
	return pos;
}

static int	project_normalized_x(float normal_x)
{
	int x_coord;

	// Convert from [-1,1] to  [0,W-1] and [0,H-1]
	x_coord = (int)((normal_x + 1.0f) * (W / 2));
	// Clamp to viewport bounds
	x_coord = clamp(x_coord, 0, W - 1);
	return x_coord;
}

static int	project_normalized_y(float normal_y)
{
	int y_coord;

	// Convert from [-1,1] to  [0,W-1] and [0,H-1]
	y_coord = (int)((1.0f - normal_y) * (H / 2));
	// Clamp to viewport bounds
	y_coord = clamp(y_coord, 0, H - 1);
	return y_coord;
}

// Counter-clockwise vertex indices for each face of the OBB cube
static void	init_vertex_list(t_bbox	*obb)
{
	obb->polys[0].vertex_list[0] = 0;		// Bottom face (y = -1)
	obb->polys[0].vertex_list[1] = 1;
	obb->polys[0].vertex_list[2] = 2;
	obb->polys[0].vertex_list[3] = 3;
	obb->polys[1].vertex_list[0] = 4;		// Top face (y = 1)
	obb->polys[1].vertex_list[1] = 5;
	obb->polys[1].vertex_list[2] = 6;
	obb->polys[1].vertex_list[3] = 7;
	obb->polys[2].vertex_list[0] = 0;		// Front face (z = 1)
	obb->polys[2].vertex_list[1] = 1;
	obb->polys[2].vertex_list[2] = 5;
	obb->polys[2].vertex_list[3] = 4;
	obb->polys[3].vertex_list[0] = 2;		// Back face (z = -1)
	obb->polys[3].vertex_list[1] = 3;
	obb->polys[3].vertex_list[2] = 7;
	obb->polys[3].vertex_list[3] = 6;
	obb->polys[4].vertex_list[0] = 0;		// Left face (x = -1)
	obb->polys[4].vertex_list[1] = 3;
	obb->polys[4].vertex_list[2] = 7;
	obb->polys[4].vertex_list[3] = 4;
	obb->polys[5].vertex_list[0] = 1;		// Right face (x = 1)
	obb->polys[5].vertex_list[1] = 2;
	obb->polys[5].vertex_list[2] = 6;
	obb->polys[5].vertex_list[3] = 5;
}

// front left bottom, front right bottom, back right bottom, back left bottom
// front left top, front right top, back right top, back left top
static void	init_bbox_pos(t_bbox *obb, float min[3], float max[3])
{
	const int	patterns[8][3] = {
	{0, 0, 1}, {1, 0, 1}, {1, 0, 0}, {0, 0, 0},
	{0, 1, 1}, {1, 1, 1}, {1, 1, 0}, {0, 1, 0}};
	int			vertex;
	int			coord;

	vertex = -1;
	coord = -1;
	while (++vertex < 8)
	{
		while (++coord < 3)
		{
			if (patterns[vertex][coord])
			{
				obb->vertices_local[vertex][coord] = max[coord];
				obb->vertices_world[vertex][coord] = obb->max[coord];
				if (coord == x)
					obb->vertices_camera[vertex][coord] = \
						project_normalized_x(obb->vertices_world[vertex][coord]);
				else if (coord == y)
					obb->vertices_camera[vertex][coord] = \
						project_normalized_y(obb->vertices_world[vertex][coord]);
			}
			else
			{
				obb->vertices_local[vertex][coord] = min[coord];
				obb->vertices_world[vertex][coord] = obb->min[coord];
				if (coord == x)
					obb->vertices_camera[vertex][coord] = \
						project_normalized_x(obb->vertices_world[vertex][coord]);
				else if (coord == y)
					obb->vertices_camera[vertex][coord] = \
						project_normalized_y(obb->vertices_world[vertex][coord]);
			}
		}
		coord = -1;
	}
	vertex = -1;
	// while (++vertex < 8)
	// {
	// 	obb->vertices_camera[vertex][0] = project_normalized_x(obb->vertices_local[vertex][0]);
	// 	obb->vertices_camera[vertex][1] = project_normalized_y(obb->vertices_local[vertex][1]);
	// 	// obb->vertices_camera[vertex][0] = project_normalized_x(max[coord]);
	// 	// obb->vertices_camera[vertex][1] = project_normalized_y(min[coord]);
	// }
}

// void	init_bbox(t_bbox *obb, t_sphere *object)
void	init_bbox(t_bbox *obb, float min[3], float max[3])
{
	float	extent;
 	float	world_size;
	int	i;

	i = -1;
 	world_size = 0.0f;
	while (++i < 3)
	{
		extent = fmaxf(fabsf(min[i]), fabsf(max[i]));
		world_size = fmaxf(world_size, extent);
	}
	i = -1;
	obb->min[x] = min[0] / world_size;
	obb->min[y] = min[1] / world_size;
	obb->min[z] = min[2] / world_size;
	obb->max[x] = max[0] / world_size;
	obb->max[y] = max[1] / world_size;
	obb->max[z] = max[2] / world_size;
	init_vertex_list(obb);
	init_bbox_pos(obb, min, max);
}
