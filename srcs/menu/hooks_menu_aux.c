/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_menu_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/08 20:57:49 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	render_bt(t_minirt *p)
{
	if (p->menu.radio_one == false)
		toogle_bool(&p->menu.radio_one);
	render_rayt(p);
	ft_printf("%s\n", "render finished");
}

void	radio_one(t_minirt *p)
{
	if (p->menu.radio_one == true)
	{
		toogle_bool(&p->menu.radio_one);
		// toogle_bool(&p->menu.click_spam);
		ft_printf("%s\n", "render cleared");
		clear_rayt(p);
	}
	else
	{
		toogle_bool(&p->menu.radio_one);
		// p->menu.click_spam = true;
		// toogle_bool(&p->menu.click_spam);
	}
}

void	color_picker(t_minirt *p, int x, int y)
{
	int offset;
	unsigned int color;

	offset = (y * MW + x) * 4;
	color = *(unsigned int *)(p->menu.img.data + offset);
	p->menu.color_picker = get_rgb(color);
	//? figure color changed here
	p->scene.figures->c = p->menu.color_picker;
	// p->menu.color_picker.rgb = color;
}

	// color = *(unsigned int *)p->menu.img.data[(y * MW + x) * 4];
	// render_menu(p);
