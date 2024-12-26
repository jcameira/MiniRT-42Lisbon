/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/26 20:10:48 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	radio_one(t_minirt *p)
{
	if (p->menu.radio_one == true)
	{
		toogle_bool(&p->menu.radio_one);
		clear_rayt(p);
		// render_menu(p);
	}
	else
	{
		toogle_bool(&p->menu.radio_one);
		render_rayt(p);
		// render_menu(p);
	}
}

t_pixel	get_rgb(int color)
{
	t_pixel	rgb;

	rgb.r = (color >> 16) & 0x000000FF;
	rgb.g = (color >> 8) & 0x000000FF;
	rgb.b = (color >> 0) & 0x000000FF;
	rgb.rgb = color;
	return (rgb);
}

void	color_picker(t_minirt *p, int x, int y)
{
	int offset;
	unsigned int color;

	offset = (y * MW + x) * 4;
	color = *(unsigned int *)(p->menu.img.data + offset);
	p->menu.color_picker = get_rgb(color);
	// p->menu.color_picker.rgb = color;
}

	// color = *(unsigned int *)p->menu.img.data[(y * MW + x) * 4];
	// render_menu(p);
