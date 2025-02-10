/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_menu_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/02/08 19:08:15 by cjoao-de         ###   ########.fr       */
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
		ft_printf("%s\n", "render restored");

		restore_image(p, p->cam.copy);
		// p->menu.click_spam = true;
		// toogle_bool(&p->menu.click_spam);
	}
}

void	radio_two(t_minirt *p)
{
	if (p->menu.radio_two == true)
	{
		toogle_bool(&p->menu.radio_two);
		// toogle_bool(&p->menu.click_spam);
		ft_printf("%s\n", "render restored");
		restore_image(p, p->cam.copy);
	}
	else
	{
		toogle_bool(&p->menu.radio_two);
		ft_printf("%s\n", "render left * red");
		restore_image(p, p->cam.left);
		// p->menu.click_spam = true;
		// toogle_bool(&p->menu.click_spam);
	}
}

void	radio_three(t_minirt *p)
{
	if (p->menu.radio_three == true)
	{
		toogle_bool(&p->menu.radio_three);
		// toogle_bool(&p->menu.click_spam);
		ft_printf("%s\n", "render restored");
		restore_image(p, p->cam.copy);
	}
	else
	{
		toogle_bool(&p->menu.radio_three);
		ft_printf("%s\n", "render right * cyan");
		restore_image(p, p->cam.right);
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
