/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/12 16:28:41 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	rayt_keys(int keysym, t_minirt *s)
{
	if (keysym == XK_Escape)
		end_minirt(s);
	return (0);
}

int	handle_keypress(int keysym, t_minirt *s)
{
	rayt_keys(keysym, s);
	menu_keys(keysym, s);
	return (0);
}

// int	mouse_rayt(int button, int x, int y, void *p)
// {
// 	(void)p;
// 	printf("Mouse in %s, button %d at %dx%d.\n", WINDOW_NAME, button, x, y);
// 	return (1);
// }
