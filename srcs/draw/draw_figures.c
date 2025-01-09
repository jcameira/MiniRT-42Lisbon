/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_figures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/04 05:08:28 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// https://www.computerenhance.com/p/efficient-dda-circle-outlines
// int other_circle(t_img img, t_circle circle)
// {
// 	int x = circle.radius;
// 	int r2 = x + x;
// 	int y = 0;
// 	int dy = -2;
// 	int dx = r2 + r2 - 4;
// 	int d = r2 - 1;
// 	pixel_put(img, circle.x_center, circle.y_center, circle.color);  // center
// 	while (y <= x)
// 	{
// 		pixel_put(img, circle.x_center + x, circle.y_center + y, circle.color);
// 		pixel_put(img, circle.x_center + x, circle.y_center - y, circle.color);
// 		pixel_put(img, circle.x_center - x, circle.y_center + y, circle.color);
// 		pixel_put(img, circle.x_center - x, circle.y_center - y, circle.color);
// 		pixel_put(img, circle.y_center + y, circle.x_center + x, circle.color);
// 		pixel_put(img, circle.y_center + y, circle.x_center - x, circle.color);
// 		pixel_put(img, circle.y_center - y, circle.x_center + x, circle.color);
// 		pixel_put(img, circle.y_center - y, circle.x_center - x, circle.color);
// 		d += dy;
// 		dy -= 4;
// 		y++;
// 		if(d < 0)
// 		{
// 			d += dx;
// 			dx -= 4;
// 			x--;
// 		}
// 	}
// 	return (0);
// }

// Function to put pixels at subsequence points
// int xc, int yc, int x, int y)
static void	pixel_put_circle(t_img *img, t_circle c, int x, int y)
{
	pixel_put(img, c.x_center + x, c.y_center + y, c.color);
	pixel_put(img, c.x_center + y, c.y_center + x, c.color);
	pixel_put(img, c.x_center + x, c.y_center - y, c.color);
	pixel_put(img, c.x_center + y, c.y_center - x, c.color);
	pixel_put(img, c.x_center - x, c.y_center + y, c.color);
	pixel_put(img, c.x_center - y, c.y_center + x, c.color);
	pixel_put(img, c.x_center - x, c.y_center - y, c.color);
	pixel_put(img, c.x_center - y, c.y_center - x, c.color);
}

// Function for circle-generation using Bresenham's algorithm
// t_circle{x_center, y_center, x, y, d, radius, color}
void draw_circle(t_img img, t_circle c)
{
	int y;
	int x;
	int d;

	x = 0;
	y = c.radius;
	d = 3 - 2 * c.radius;
	pixel_put_circle(&img, c, x, y);
	while (y >= x)
	{
		// check for decision parameter and correspondingly update d, y
		if (d > 0) {
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		// Increment x after updating decision parameter
		x++;
		// Draw the circle using the new coordinates
		pixel_put_circle(&img, c, x, y);
	}
}

// brute force a filled circle
void draw_circle_fill(t_img img, t_circle c)
{
	int y;
	int x;
	int dot_r;

	y = -c.radius;
	x = -c.radius;
	dot_r = c.radius * c.radius;
	while (y <= c.radius)
	{
		while (x <= c.radius)
		{
			if (x * x + y * y <= dot_r)
				pixel_put(&img, c.x_center + x, c.y_center + y, c.color);
			x++;
		}
		x = -c.radius;
		y++;
	}
}

void	draw_radio(t_minirt *s, t_circle c, char *text, bool on_off)
{
	int	radius;
	int	color_copy;

	color_copy = c.color;
	radius = c.radius;
	draw_circle(s->menu.img, c);
	c.radius -= 7;
	if (on_off)
	{
		c.color = GREEN;
		draw_circle_fill(s->menu.img, c);
	}
	c.color = GRAY;
	draw_circle(s->menu.img, c);
	c.color = color_copy;
	c.radius = radius;
	mlx_string_put(s->mlx, s->win_menu, c.x_center + c.radius / 2 + 20,
		c.y_center + c.radius / 2 - 5, BLACK, text);
}

//todo remove alpha logic
int	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	if (rect.color >> 24 != 0)
	{
		while (i < rect.y + rect.height)
		{
			j = rect.x;
			while (j < rect.x + rect.width)
				pixel_put_alpha(img, j++, i, rect.color);
			++i;
		}
	}
	else
	{
		while (i < rect.y + rect.height)
		{
			j = rect.x;
			while (j < rect.x + rect.width)
				pixel_put(img, j++, i, rect.color);
			++i;
		}
	}
	return (0);
}
