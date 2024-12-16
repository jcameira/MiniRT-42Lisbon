/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wireframe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/16 20:39:29 by cjoao-de         ###   ########.fr       */
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
