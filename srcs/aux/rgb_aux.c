/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 04:31:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/12 21:06:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pixel	add_pixel_color(t_pixel real_p, t_pixel to_add)
{
	t_pixel	new_color;

	new_color.r = real_p.r + to_add.r;
	new_color.g = real_p.g + to_add.g;
	new_color.b = real_p.b + to_add.b;
	new_color.rgb = new_color.r << 16 | new_color.g << 8 | new_color.b;
	return (new_color);
}

t_pixel	scale_pixel_color(t_pixel real_p, float scalar)
{
	t_pixel	new_color;

	new_color.r = real_p.r * scalar;
	new_color.g = real_p.g * scalar;
	new_color.b = real_p.b * scalar;
	new_color.rgb = new_color.r << 16 | new_color.g << 8 | new_color.b;
	return (new_color);
}

// send color int, get t_pixel
t_pixel	get_rgb(int color)
{
	t_pixel	rgb;

	rgb.r = (color >> 16) & 0x000000FF;
	rgb.g = (color >> 8) & 0x000000FF;
	rgb.b = (color >> 0) & 0x000000FF;
	rgb.rgb = color;
	return (rgb);
}

// send R G B normalized float, get t_pixel
t_pixel	color(float r, float g, float b)
{
	t_pixel	color;

	color.r = 255 * r;
	color.g = 255 * g;
	color.b = 255 * b;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}
