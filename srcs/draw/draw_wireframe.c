/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/14 00:56:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// TODO recheck vertices and poly list, arrive on the wrong order
// 	Draw a cube made of wires surrouding the object
void draw_obb(t_minirt *s, t_bbox *obb, int color)
{
	int i;
	int j;
	int start[2];
	int end[2];

	i = -1;
	while (++i < 6)	// Loop through vertices of each face
	{
		j = -1;
		while (++j < 4)
		{
			// Get current and next vertex (wrap to 0)
			int curr_vertex = obb->polys[i].vertex_list[j];
			int next_vertex = obb->polys[i].vertex_list[(j + 1) % 4];
			// Get 3D coordinates
			start[0] = obb->vertices_camera[curr_vertex][0];
			start[1] = obb->vertices_camera[curr_vertex][1];
			end[0] = obb->vertices_camera[next_vertex][0];
			end[1] = obb->vertices_camera[next_vertex][1];
			draw_line(s, (t_line)
					{{start[0], start[1]}, {end[0], end[1]}, 0, 0, 0, 0, 0, NULL, color});
		}
	}
	return ;
}
	// obb->num_vertices = 8;
	// obb->num_polys = 6;

/*
void Draw_Object_Wire(t_minirt *s, t_bbox obb)
{
	// this function draws an object out of wires
	int curr_poly,		// the current polygon
		curr_vertex,	// the current vertex
		vertex;			// vertex index
	float x1,y1,z1,		// working variables
		x2,y2,z2;
	int ix1,iy1,		// integers used to hold screen coordinates
		ix2,iy2;

	// compute position of object in world
	for (curr_poly=0; curr_poly<obb->num_polys; curr_poly++)
	{

		// is this polygon visible?
		//? if (obb->polys[curr_poly].visible==0 || obb->polys[curr_poly].clipped )
		//? 	continue;
		// printf("\npolygon #%d",curr_poly);

		for (curr_vertex=0; curr_vertex<obb->polys[curr_poly].num_points-1; curr_vertex++)
		{
			// extract two endpoints
			vertex=obb->polys[curr_poly].vertex_list[curr_vertex];
			x1 = obb->vertices_camera[vertex].x;
			y1 = obb->vertices_camera[vertex].y;
			z1 = obb->vertices_camera[vertex].z;

			vertex=obb->polys[curr_poly].vertex_list[curr_vertex+1];
			x2 = obb->vertices_camera[vertex].x;
			y2 = obb->vertices_camera[vertex].y;
			z2 = obb->vertices_camera[vertex].z;

			// convert to screen ccordinates
			x1=(HALF_SCREEN_WIDTH  + x1*viewing_distance/z1);
			y1=(HALF_SCREEN_HEIGHT - ASPECT_RATIO*y1*viewing_distance/z1);
			x2=(HALF_SCREEN_WIDTH  + x2*viewing_distance/z2);
			y2=(HALF_SCREEN_HEIGHT - ASPECT_RATIO*y2*viewing_distance/z2);

			// convert floats to integers for line clipper
			ix1=(int)x1;
			iy1=(int)y1;
			ix2=(int)x2;
			iy2=(int)y2;

			//! draw clipped lines
			// if (Clip_Line(&ix1,&iy1,&ix2,&iy2))
			// {
			// Draw_Line((int)ix1,(int)iy1,(int)ix2,(int)iy2,
			// 			(unsigned char)obb->polys[curr_poly].color,
			// 			double_buffer, s);
			// } // end if clip
		} // end for vertex

		// close polygon
		ix1=(int)x2;
		iy1=(int)y2;

		// extract starting point again to close polygon
		vertex=obb->polys[curr_poly].vertex_list[0];
		x2 = obb->vertices_camera[vertex].x;
		y2 = obb->vertices_camera[vertex].y;
		z2 = obb->vertices_camera[vertex].z;

		// compute screen coordinates
		x2=(HALF_SCREEN_WIDTH  + x2*viewing_distance/z2);
		y2=(HALF_SCREEN_HEIGHT - ASPECT_RATIO*y2*viewing_distance/z2);

		// convert floats to integers
		ix2=(int)x2;
		iy2=(int)y2;

		//! draw clipped lines
		// if (Clip_Line(&ix1,&iy1,&ix2,&iy2))
		//    {
		//    Draw_Line((int)ix1,(int)iy1,(int)ix2,(int)iy2,
		//              (unsigned char)obb->polys[curr_poly].color,
		//              double_buffer, s);
		//} // end if clip
	} // end for curr_poly
} // end Draw_Object_Wire
*/
