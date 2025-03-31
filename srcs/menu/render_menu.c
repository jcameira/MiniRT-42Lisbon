/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/31 21:09:06 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	draw_color_picker(t_minirt *s)
{
	t_rect	rect;

	rect = (t_rect){MW - 322, 8, 304, 24, GREEN};
	render_rect(&s->menu.img, rect);
	// todo interactive color display from figure
	// rect = (t_rect){MW - 320, 10, 300, 20, s->menu.color_picker.rgb};
	rect = (t_rect){MW - 320, 10, 300, 20, object_content(s->menu.objects)->mat.c.rgb};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){MW - s->assets.bt_clrpick.width - 32, 38, \
		s->assets.bt_clrpick.width + 4, s->assets.bt_clrpick.height + 4, GREEN};
	render_rect(&s->menu.img, rect);
	join_xpm_img(s->menu.img, s->assets.bt_clrpick, \
		MW - s->assets.bt_clrpick.width - 30, 40, 0);
}

int	render_menu(t_minirt *s)
{
	// t_rect	rect;

	set_bk_color(s->menu.img.data, WHITE, MW * MH * 4);
	draw_color_picker(s);

	//? figure color changed here
	join_xpm_img(s->menu.img, s->assets.bt_render, (MW - s->assets.bt_render.width) / 2, 360, 0);
	// draw_circle(s->menu.img, (t_circle){110, 500, 20, BLACK});
	// draw_circle_fill(s->menu.img, (t_circle){110, 500, 13, GREEN});
	// mlx_string_put(s->mlx, s->win_menu, 120, 500, BLACK, NO_ARGS);
	// mlx_set_font(s->mlx, s->win_menu, FONT_A);
	mlx_put_image_to_window(s->mlx, s->win_menu, s->menu.img.image, 0, 0);
	// object_type(p->scene.objects);
	mlx_string_put(s->mlx, s->win_menu, 200, 200, BLACK, f_name(object_type(s->menu.objects)));
	if (object_material(s->menu.objects).type == 4)
		mlx_string_put(s->mlx, s->win_menu, 200, 250, BLACK, "Light on");
	else
		mlx_string_put(s->mlx, s->win_menu, 200, 250, BLACK, "Light off");

	// mlx_string_put(s->mlx, s->win_menu, 200, 200, BLACK, f_name(s->menu.figures->type));
	// todo interactive color display from figure
	//! TODO ft_printf("%s\n", f_name(s->menu.figures->type));

	//? all string put must be after put_image_to_window
	draw_radio(s, (t_circle){30, 450, 20, BLACK}, "<- Click ME", s->menu.radio_one);
	draw_radio(s, (t_circle){30, 500, 20, BLACK}, "<- LEFT_RIGHT", s->menu.radio_two);
	draw_radio(s, (t_circle){30, 550, 20, BLACK}, "<- CLEAN", s->menu.radio_three);
	draw_radio(s, (t_circle){30, 600, 20, BLACK}, "<- ANAGLYPH", s->menu.radio_four);
	// draw_radio(s, (t_circle){30, 300, 20, BLACK}, NO_ARGS, false);
	return (0);
}

void	clear_rayt(t_minirt *s)
{
	set_bk_color(s->scene.cam.img.data, CYAN, W * H * 4);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
}
