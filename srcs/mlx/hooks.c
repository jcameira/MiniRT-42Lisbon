/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/09 21:12:37 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// int	handle_keypress(int keysym, t_minirt *s)
// {
	// if (keysym == XK_Escape)
		// end_minirt(s);
	// //reset
	// if (keysym == XK_r)
	// 	init_shader(s, s->type, s->julia_r, s->julia_c);
	// if (keysym == XK_Up || keysym == XK_w)
	// 	// todo stuff
	// if (keysym == XK_Down || keysym == XK_s)
	// if (keysym == XK_Left || keysym == XK_a)
	// if (keysym == XK_Right || keysym == XK_d)
	// more_keypress(keysym, s);
	// return (0);
// }
static int	rayt_keys(int keysym, t_minirt *s)
{
	if (keysym == XK_Escape)
		end_minirt(s);
	return (0);
}

static int	menu_keys(int keysym, t_minirt *s)
{
	if (keysym == XK_Tab)
	{
	// todo interactive color display from figure
		s->menu.figures = s->menu.figures->next;
		if (s->menu.figures == NULL)
		{
			s->menu.figures = s->scene.figures;
			ft_printf("looped figure list\n");
		}
	}
	return (render_menu(s), 0);
}

int	handle_keypress(int keysym, t_minirt *s)
{
	rayt_keys(keysym, s);
	menu_keys(keysym, s);
	return (0);
}

int	mouse_rayt(int button, int x, int y, void *p)
{
	(void)p;
	printf("Mouse in %s, button %d at %dx%d.\n", WINDOW_NAME, button, x, y);
	return (1);
}
