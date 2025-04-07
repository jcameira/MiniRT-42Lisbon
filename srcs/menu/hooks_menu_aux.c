/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_menu_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/07 20:38:24 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	render_bt(t_minirt *p)
{
	toogle_bool(&p->render);
	if (p->render == false)
	{
		ft_printf("%s\n", "render finished");
		dup_image(p->scene.cam.copy, p->scene.cam.img.data);
	}
	else
		ft_printf("%s\n", "render starting");
}

void	radio_one(t_minirt *p)
{
	// if (p->menu.radio_one == true)
	// {
	// 	toogle_bool(&p->menu.radio_one);
	// 	// toogle_bool(&p->menu.click_spam);
	// 	ft_printf("%s\n", "render cleared");
	// 	clear_rayt(p);
	// }
	// else
	// {
		toogle_bool(&p->menu.radio_one);
		ft_printf("%s\n", "render restored");
		restore_image(p, p->scene.cam.copy);
		// p->menu.click_spam = true;
		// toogle_bool(&p->menu.click_spam);
	// }
}

void	radio_two(t_minirt *p)
{
	if (p->menu.radio_two == true)
	{
		toogle_bool(&p->menu.radio_two);
		ft_printf("%s\n", "render left * red");
		restore_image(p, p->scene.cam.red);
	}
	else
	{
		toogle_bool(&p->menu.radio_two);
		ft_printf("%s\n", "render left * cyan");
		restore_image(p, p->scene.cam.cyan);
	}
}

void	radio_three(t_minirt *p)
{
	toogle_bool(&p->menu.radio_three);
	ft_printf("%s\n", "clean");
	clean(p->scene.cam.clean);
	restore_image(p, p->scene.cam.clean);
}

void	radio_four(t_minirt *p)
{
	// if (p->menu.radio_three == true)
	// {
	// 	toogle_bool(&p->menu.radio_three);
	// 	// toogle_bool(&p->menu.click_spam);
	// 	ft_printf("%s\n", "render restored");
	// 	restore_image(p, p->scene.cam.copy);
	// }
	// else
	// {
		create_anaglyph_main(p);
		toogle_bool(&p->menu.radio_four);
		ft_printf("%s\n", "render anaglyph");
		restore_image(p, p->scene.cam.anaglyph);
		// p->menu.click_spam = true;
		// toogle_bool(&p->menu.click_spam);
	// }
}

void	color_picker(t_minirt *p, int x, int y)
{
	t_object		*content;
	int				offset;
	unsigned int	color;

	offset = (y * MW + x) * 4;
	color = *(unsigned int *)(p->menu.img.data + offset);
	p->menu.color_picker = get_rgb(color);
	//? figure color changed here
	content = object_content(p->menu.objects);
	content->mat.c = p->menu.color_picker;
	p->menu.color_picker.rgb = color;
}

	// color = *(unsigned int *)p->menu.img.data[(y * MW + x) * 4];
	// render_menu(p);
