/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/12 14:12:36 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	line_down(t_line *line)
{
	*(unsigned int *)line->pix = line->color;	// inline pixel_put
	line->error += line->dy;	//	 adjust the error term
	if (line->error > line->dx)	// test if error has overflowed
	{
		line->error -= line->dx;
		line->pix += line->y_inc; // move to next line
	} // end if error overflowed
	line->pix += line->x_inc;	// move to the next pixel
}

static void	line_up(t_line *line)
{
	*(unsigned int *)line->pix = line->color;	// inline pixel_put
	line->error += line->dx; // adjust the error term
	if (line->error > 0) // test if error overflowed
	{
		line->error -= line->dy;
		line->pix += line->x_inc;
	} // end if error overflowed
	line->pix += line->y_inc;
}

// init line vars
static void	init_line(t_line *line)
{
	line->error = 0;
	line->dx = line->dest[x] - line->origin[x];// compute horizontal and vertical deltas
	line->dy = line->dest[y] - line->origin[y];
	if (line->dx >= 0)	// test which direction the line is going in i.e. slope angle
		line->x_inc = 4;
	else
	{
		line->x_inc = -4;
		line->dx = -line->dx;	// need absolute value
	}
	if (line->dy >= 0)	// test y component of slope
		line->y_inc = W * 4; // width * 4 bytes // end if line is moving down
	else
	{
		line->y_inc = -W * 4;
		line->dy = -line->dy;	// need absolute value
	}
}

//! line is not perpendicular, or is it?
//todo recheck Normitagge
// this function draws a line from o[x],o[y] to d[x],d[y]
// using differential error terms (based on Bresenahams work)
void	draw_line(t_minirt *s, t_line line)
{
	int	i;

	i = -1;
	line.pix = s->scene.cam.img.data + (((line.origin[y] * H) << 2) + (line.origin[x] << 2));
	init_line(&line);
	if (line.dx > line.dy)
	{
		while (++i <= line.dx)
			line_down(&line);
	}
	else
	{
		while (++i <= line.dy)
			line_up(&line);
	}
}
