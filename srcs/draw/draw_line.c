/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/13 22:24:37 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	line_down(t_line *line)
{
	*(unsigned int *)line->pix = line->color;
	line->error += line->dy;
	if (line->error > line->dx)
	{
		line->error -= line->dx;
		line->pix += line->y_inc;
	}
	line->pix += line->x_inc;
}

static void	line_up(t_line *line)
{
	*(unsigned int *)line->pix = line->color;
	line->error += line->dx;
	if (line->error > 0)
	{
		line->error -= line->dy;
		line->pix += line->x_inc;
	}
	line->pix += line->y_inc;
}

// init line vars
static void	init_line(t_line *line)
{
	line->error = 0;
	line->dx = line->dest[x] - line->origin[x];
	line->dy = line->dest[y] - line->origin[y];
	if (line->dx >= 0)
		line->x_inc = 4;
	else
	{
		line->x_inc = -4;
		line->dx = -line->dx;
	}
	if (line->dy >= 0)
		line->y_inc = W * 4;
	else
	{
		line->y_inc = -W * 4;
		line->dy = -line->dy;
	}
}

// this function draws a line from o[x],o[y] to d[x],d[y]
// using differential error terms (based on Bresenahams work)
void	draw_line(t_img img, t_line line)
{
	int	i;

	i = -1;
	line.pix = img.data + (((line.origin[y] * H) << 2) + (line.origin[x] << 2));
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
