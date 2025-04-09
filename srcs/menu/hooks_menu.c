/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/09 21:36:19 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	mouse_menu(int button, int x, int y, void *param)
{
	t_minirt *p;
	(void)button;

	p = (t_minirt *)param;
	if ((x >= 20 && x <= 40) && (y >= 440 && y <= 460))
		radio_one(p);
	if ((x >= 20 && x <= 40) && (y >= 490 && y <= 510))
		radio_two(p);
	if ((x >= 20 && x <= 40) && (y >= 540 && y <= 560))
		radio_three(p);
	if ((x >= 20 && x <= 40) && (y >= 590 && y <= 610))
		radio_four(p);
	if ((x >= (MW - 134) / 2 && x <= (MW + 134) / 2) && (y >= 360 && y <= 414))
		render_bt(p);
	if ((x >= MW - p->assets.bt_clrpick.img.width - 30 && x <= MW - 30) \
		&& (y >= 40 && y <= p->assets.bt_clrpick.img.height + 40))
		color_picker(p, x, y);
	if ((x >= 40 && x <= p->assets.bt_bright.img.width + 40) \
		&& (y >= 278 && y <= 278 + p->assets.bt_bright.img.height))
		brightness_picker(p, x, y);
	// printf("Mouse in %s, button %d at %dx%d.\n", MENU_NAME, button, x, y);
	return (render_menu(p), 1);
}

int	menu_keys(int keysym, t_minirt *s)
{
	if (keysym == XK_Tab)
	{
	// todo interactive color display from figure
		s->menu.objects = s->menu.objects->next;
		if (s->menu.objects == NULL)
		{
			s->menu.objects = s->scene.objects;
			ft_printf("looped figure list\n");
		}
	}
	else if (keysym == XK_1 || keysym == XK_2 || keysym == XK_3 || keysym == XK_4)
	{
		set_material(s->menu.objects, keysym);
	}
	return (render_menu(s), 0);
}
