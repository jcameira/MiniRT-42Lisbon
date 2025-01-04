/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 04:31:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/04 04:37:31 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

// send R G B float, get t_pixel
t_pixel	color(float r, float g, float b)
{
	t_pixel	color;

	color.r = 255 * r;
	color.g = 255 * g;
	color.b = 255 * b;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}
