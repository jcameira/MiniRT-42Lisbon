/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_oob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/19 20:16:58 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Counter-clockwise vertex indices for each face of the OBB cube
void	init_vertex_list(t_obb	*obb)
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

void	init_obb_pos(t_obb	*obb, float min[3], float max[3])
{
	obb->vertices_local[0][x] = min[x];		// Front left
	obb->vertices_local[0][y] = min[y];
	obb->vertices_local[0][z] = max[z];
	obb->vertices_local[1][x] = max[x];		// Front right
	obb->vertices_local[1][y] = min[y];
	obb->vertices_local[1][z] = max[z];
	obb->vertices_local[2][x] = max[x];		// Back right
	obb->vertices_local[2][y] = min[y];
	obb->vertices_local[2][z] = min[z];
	obb->vertices_local[3][x] = min[x];		// Back left
	obb->vertices_local[3][y] = min[y];
	obb->vertices_local[3][z] = min[z];
	obb->vertices_local[4][x] = min[x];		// Front left
	obb->vertices_local[4][y] = max[y];
	obb->vertices_local[4][z] = max[z];
	obb->vertices_local[5][x] = max[x];		// Front right
	obb->vertices_local[5][y] = max[y];
	obb->vertices_local[5][z] = max[z];
	obb->vertices_local[6][x] = max[x];		// Back right
	obb->vertices_local[6][y] = max[y];
	obb->vertices_local[6][z] = min[z];
	obb->vertices_local[7][x] = min[x];		// Back left
	obb->vertices_local[7][y] = max[y];
	obb->vertices_local[7][z] = min[z];
}

void	init_obb(t_obb	*obb, t_sphere object)
{
	float	min[3];
	float	max[3];
	// Initialize min array
	min[x] = object.c[x] - object.r;
	min[y] = object.c[y] - object.r;
	min[z] = object.c[z] - object.r;

	// Initialize max array
	max[x] = object.c[x] + object.r;
	max[y] = object.c[y] + object.r;
	max[z] = object.c[z] + object.r;
	init_obb_pos(obb, min, max);
	init_vertex_list(obb);
}
