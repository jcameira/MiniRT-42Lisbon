/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/30 19:37:09 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_bbox draw_obb(t_minirt *s, t_sphere object, int color)
{
	t_bbox obb;
	int i, j;
	int start[2], end[2];
	float v1[3], v2[3];
	obb.num_vertices = 8;
	obb.num_polys = 6;
	init_bbox(&obb, object);
	obb.world_pos[x] = 0;
	obb.world_pos[y] = 0;
	obb.world_pos[z] = 300;
	// viewing_distance = 250;
	int scale = 4;
	// int screen = 600;
	// Loop through each face
	i = 0;
	// while (done)
	// {
	// //! Rotate_Object((object_ptr)&test_object,2,4,6);
	// // convert the local coordinates into camera coordinates for projection
	// // note the viewer is at (0,0,0) with angles 0,0,0 so the transformaton
	// // is simply to add the world position to each local vertex
	// 	for (index=0; index<obb.num_vertices; index++)
	// 	{
	// 		obb.vertices_camera[index][x] =
	// 			obb.vertices_local[index][x]+obb.world_pos[x];
	// 		obb.vertices_camera[index][y] =
	// 			obb.vertices_local[index][y]+obb.world_pos[y];
	// 		obb.vertices_camera[index][z] =
	// 			obb.vertices_local[index][z]+obb.world_pos[z];
	// 	} // end for index

	// 	// draw the object
	// 	Draw_Object_Wire(&obb, s);
	// }
	while (i < 6)
	{
		// Loop through vertices of each face
		j = 0;
		while (j < 4)
		{
			// Get current and next vertex (wrap to 0)
			int curr_vertex = obb.polys[i].vertex_list[j];
			int next_vertex = obb.polys[i].vertex_list[(j + 1) % 4];

			// Get 3D coordinates
			v1[0] = obb.vertices_local[curr_vertex][0];
			v1[1] = obb.vertices_local[curr_vertex][1];
			v1[2] = obb.vertices_local[curr_vertex][2];

			v2[0] = obb.vertices_local[next_vertex][0];
			v2[1] = obb.vertices_local[next_vertex][1];
			v2[2] = obb.vertices_local[next_vertex][2];

			// Convert 3D to 2D coordinates
			// + (i * s->cam.vp.deltah[0]) + (j * s->cam.vp.deltav[0])
			// start[0] = (int)(v1[0] * s->cam.vp.scale + s->cam.vp.offset_x);
			// start[1] = (int)(v1[1] * s->cam.vp.scale + s->cam.vp.offset_y);
			// end[0] = (int)(v2[0] * s->cam.vp.scale + s->cam.vp.offset_x);
			// end[1] = (int)(v2[1] * s->cam.vp.scale + s->cam.vp.offset_y);

			start[0] = (int)(v1[0] + 3) * scale;
			start[1] = (int)(v1[1] + 3) * scale;
			end[0] = (int)(v2[0] + 3) * scale;
			end[1] = (int)(v2[1] + 3) * scale;

			// Draw the line
			// draw_line(s, (t_line){start, end, 0, 0, color});
			draw_line(s, (t_line)
					{{start[0], start[1]}, {end[0], end[1]}, 0, 0, 0, 0, 0, NULL, color});
			j++;
		}
		i++;
	}
	return (obb);
}

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
