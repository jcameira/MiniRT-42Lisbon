/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_figures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/09 17:05:04 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
