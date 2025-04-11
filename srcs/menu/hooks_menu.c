/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/11 16:12:17 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	menu_mouse(int button, int x, int y, void *param)
{
	t_minirt *p;

	p = (t_minirt *)param;
	if (button == 1)
	{
		if ((x >= 40 && x <= 80) && (y >= 430 && y <= 470))
			radio_one(p);
		if ((x >= 40 && x <= 80) && (y >= 530 && y <= 570))
			radio_two(p);
		if ((x >= 40 && x <= 80) && (y >= 580 && y <= 620))
			radio_four(p);
		if ((x >= MW - 181 - 80 && x <= MW - 80) && (y >= 350 && y <= 404))
			render_bt(p);
		if ((x >= MW - p->assets.bt_clrpick.img.width - 30 && x <= MW - 30) \
			&& (y >= 40 && y <= p->assets.bt_clrpick.img.height + 40))
			color_picker(p, x, y);
		if ((x >= 40 && x <= p->assets.bt_gradient.img.width + 40) \
			&& (y >= 278 && y <= 278 + p->assets.bt_gradient.img.height))
			brightness_picker(p, x, y);
		if ((x >= 40 && x <= 320) && (y >= 350 && y <= 404))
			set_quality(p, x);
	}
	printf("Mouse in %s, button %d at %dx%d.\n", MENU_NAME, button, x, y);
	return (render_menu(p), 1);
}

int	menu_keys(int keysym, t_minirt *s)
{
	if (keysym == XK_Tab)
	{
		s->menu.objects = s->menu.objects->next;
		if (s->menu.objects == NULL)
		{
			s->menu.objects = s->scene.objects;
			ft_printf("looped figure list\n");
		}
	}
	// else if (keysym == XK_1 || keysym == XK_2 || keysym == XK_3 || keysym == XK_4)
	else if (keysym >= XK_1 && keysym <= XK_6)
		set_material(s->menu.objects, keysym);
	return (render_menu(s), 0);
}
