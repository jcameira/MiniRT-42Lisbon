/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/19 18:41:26 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	handle_keypress(int keysym, t_minirt *s)
{
	if (keysym == XK_Escape)
		end_minirt(s);
	// //reset
	// if (keysym == XK_r)
	// 	init_shader(s, s->type, s->julia_r, s->julia_c);
	// if (keysym == XK_Up || keysym == XK_w)
	// 	// todo stuff
	// if (keysym == XK_Down || keysym == XK_s)
	// if (keysym == XK_Left || keysym == XK_a)
	// if (keysym == XK_Right || keysym == XK_d)
	more_keypress(keysym, s);
	return (0);
}

int	more_keypress(int keysym, t_minirt *s)
{
	if (s->type == 0)
	{
		if (keysym == XK_i)
			s->stuff++;
	}
	else
	{
		if (keysym == XK_i)
			s->stuff += 2;
	}
	return (render(s), 0);
}

// TODO logic para detetar falsos movimentos do mouse, not needed.
int	handle_buttons(int button, int x, int y, t_minirt *s)
{
	(void)x;
	(void)y;
	if (button == Button1 && x < H)	//left click
	{
		s->stuff=1;
	}
	// todo plug functions here
	if (button == Button5)	//scroll
		s->stuff *= 1.05;
	if (button == Button4)	//scroll
		s->stuff *= 0.95;
	return (render(s), 0);
}
