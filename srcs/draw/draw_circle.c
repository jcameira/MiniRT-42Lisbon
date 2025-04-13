/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/13 22:25:26 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
void	draw_circle(t_img img, t_circle c)
{
	int	y;
	int	x;
	int	d;

	x = 0;
	y = c.radius;
	d = 3 - 2 * c.radius;
	pixel_put_circle(&img, c, x, y);
	while (y >= x)
	{
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		x++;
		pixel_put_circle(&img, c, x, y);
	}
}

// brute force a filled circle
void	draw_circle_fill(t_img img, t_circle c)
{
	int	y;
	int	x;
	int	dot_r;

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
