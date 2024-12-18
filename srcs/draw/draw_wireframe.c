/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/18 20:58:25 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// int o[x], int o[y], int d[x],int d[y]y1, unsigned char color,unsigned char *vb_start)
// this function draws a line from o[x],o[y] to d[x],d[y] using differential error
// terms (based on Bresenahams work)
// int o[2], int d[2]: (o)rigin coords, (d)estination coords
void draw_line(t_minirt *s, int o[2], int d[2], int color)
{
	int		dx;			// difference in x's
	int		dy;             // difference in y's
	int		x_inc;          // amount in pixel space to move during drawing
	int		y_inc;          // amount in pixel space to move during drawing
	int		error;        // the discriminant i.e. error i.e. decision variable
	int		i;          // used for looping
	char	*pix;		// pointer to img data position

	error = 0;        // the discriminant i.e. error i.e. decision variable
// pre-compute first pixel address in video buffer

	pix = s->cam.img.data + ( ((o[y] * H) << 2) + (o[x] << 2));
	// pix = s->img.data + ( (((o[y]<<8) + (o[y]<<6)) <<2) + (o[x]<<2) );

// compute horizontal and vertical deltas
	dx = d[x] - o[x];
	dy = d[y] - o[y];
// test which direction the line is going in i.e. slope angle
	if (dx >= 0)
		x_inc = 4;
	else
	{
		x_inc = -4;
		dx = -dx;  // need absolute value
	} // end else moving left
// test y component of slope
	if (dy >= 0)
		y_inc = W * 4; // width * 4 bytes // end if line is moving down
	else
	{
		y_inc = -W * 4;
		dy = -dy;	// need absolute value
	} // end else moving up
// now based on which delta is greater we can draw the line
	i = -1;
	if (dx > dy)	// |slope| <= 1
	{
		while (++i <= dx)	// draw the line
		{
			*(unsigned int *)pix = color;	// set the pixel
			error += dy;//	 adjust the error term
			if (error > dx) // test if error has overflowed
			{
				error -= dx;
				pix += y_inc; // move to next line
			} // end if error overflowed
			pix += x_inc;	// move to the next pixel
		}
	}
	else	// |slope| > 1
	{
		while (++i <= dy)	// draw the line
		{
			*(unsigned int *)pix = color;	// set the pixel
			error += dx; // adjust the error term
			if (error > 0) // test if error overflowed
			{
				error -= dy;
				pix += x_inc;
			} // end if error overflowed
			pix += y_inc;
		}
	}
}

t_obb draw_obb(t_minirt *s, t_sphere object, int color)
{
	t_obb obb;
	int i, j;
	int start[2], end[2];
	float v1[3], v2[3];
	init_obb(&obb, object);
	int scale = 4;
	// int screen = 600;
	// Loop through each face
	i = 0;
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
			draw_line(s, start, end, color);
			j++;
		}
		i++;
	}
	return (obb);
}

// t_obb	draw_obb(t_minirt *s, t_sphere object, int color)
// {
// 	(void)object;
// 	(void)color;
// 	t_obb	obb;
// 	int i;

// 	init_obb(&obb);
// 	i = 0;
// 	while (i < 6)
// 		draw_line(s, int[3], int[3], color)


// 	return (obb);
// }
