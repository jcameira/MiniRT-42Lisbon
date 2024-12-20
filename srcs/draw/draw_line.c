/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/20 21:58:58 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// this function draws a line from o[x],o[y] to d[x],d[y]
// using differential error terms (based on Bresenahams work)
// TODO line is not perpendicular, recheck Normitagge
// ? check if code is wrong, or line really should be diagonal
void draw_line(t_minirt *s, t_line line)
{
	// char	*pix;		// pointer to img.data position
	int		i;

	i = -1;
	line.pix = s->cam.img.data + (((line.origin[y] * H) << 2) + (line.origin[x] << 2));
	init_line(&line);
	if (line.dx > line.dy)	// |slope| <= 1
	{
		while (++i <= line.dx)	// draw the line
		{
			line_down(&line);
			// *(unsigned int *)pix = line.color;	// inline pixel_put
			// line.error += line.dy;	//	 adjust the error term
			// if (line.error > line.dx)	// test if error has overflowed
			// {
			// 	line.error -= line.dx;
			// 	pix += line.y_inc; // move to next line
			// } // end if error overflowed
			// pix += line.x_inc;	// move to the next pixel
		}
	}
	else	// |slope| > 1
	{
		while (++i <= line.dy)	// draw the line
		{
			line_up(&line);
			// *(unsigned int *)pix = line.color;	// inline pixel_put
			// line.error += line.dx; // adjust the error term
			// if (line.error > 0) // test if error overflowed
			// {
			// 	line.error -= line.dy;
			// 	pix += line.x_inc;
			// } // end if error overflowed
			// pix += line.y_inc;
		}
	}
}

void	line_down(t_line *line)
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

void	line_up(t_line *line)
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
void	init_line(t_line *line)
{
	line->error = 0;
	line->dx = line->dest[x] - line->origin[x];// compute horizontal and vertical deltas
	line->dy = line->dest[y] - line->origin[y];
	if (line->dx >= 0)// test which direction the line is going in i.e. slope angle
		line->x_inc = 4;
	else
	{
		line->x_inc = -4;
		line->dx = -line->dx;  // need absolute value
	}
	if (line->dy >= 0)// test y component of slope
		line->y_inc = W * 4; // width * 4 bytes // end if line is moving down
	else
	{
		line->y_inc = -W * 4;
		line->dy = -line->dy;	// need absolute value
	}
}
