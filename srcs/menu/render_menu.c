/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/09 21:58:06 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
rect draw order
current color background > main background > current color
*/
static void	draw_color_picker(t_minirt *s)
{
	t_rect	rect;

	rect = (t_rect){MW - 322, 8, 304, 24, GREEN};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){MW - s->assets.bt_clrpick.img.width - 32, 38, \
		s->assets.bt_clrpick.img.width + 4, \
		s->assets.bt_clrpick.img.height + 4, GREEN};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){MW - 320, 10, 300, 20, \
		object_content(s->menu.objects)->mat.c.rgb};
	render_rect(&s->menu.img, rect);
	join_xpm_img(s->menu.img, s->assets.bt_clrpick, \
		MW - s->assets.bt_clrpick.img.width - 30, 40);
}

static void	draw_brightness_picker(t_minirt *s)
{
	t_rect	rect;
	int		x_pos;

	rect = (t_rect){38, 276, \
		s->assets.bt_bright.img.width + 4, \
		s->assets.bt_bright.img.height + 4, GREEN};
	render_rect(&s->menu.img, rect);
	join_xpm_img(s->menu.img, s->assets.bt_bright, 40, 278);
	x_pos = (int)(object_content(s->menu.objects)->mat.br \
		* s->assets.bt_bright.img.width) + 40;
	rect = (t_rect){x_pos, 278, 2, 40, CYAN};
	render_rect(&s->menu.img, rect);
}

int	render_menu(t_minirt *s)
{
	set_bk_color(s->menu.img.data, WHITE, MW * MH * 4);
	join_xpm_sprite(s->menu.img, s->assets.bt_render, \
		(MW - s->assets.bt_render.img.width) / 2, 360, s->render);
	join_xpm_sprite(s->menu.img, s->assets.label_figures, 40, 40, \
		object_type(s->menu.objects));
	join_xpm_sprite(s->menu.img, s->assets.label_materials, 40, 134, \
		object_material(s->menu.objects).type - 1);
	draw_color_picker(s);
	draw_brightness_picker(s);
	mlx_put_image_to_window(s->mlx, s->win_menu, s->menu.img.image, 0, 0);
	draw_help(s, 300, 455);
	draw_radio(s, (t_circle){40, 450, 20, BLACK}, "Restore", s->menu.radio_one);
	// draw_radio(s, (t_circle){40, 500, 20, BLACK}, "Clean", s->menu.radio_three);
	draw_radio(s, (t_circle){40, 550, 20, BLACK}, "Red / Cyan", s->menu.radio_two);
	draw_radio(s, (t_circle){40, 600, 20, BLACK}, "Anaglyph", s->menu.radio_four);
	return (0);
}

// mlx_string_put(s->mlx, s->win_menu, 200, 200, BLACK, f_name(object_type(s->menu.objects)));
// if (object_material(s->menu.objects).type == 4)
// 	mlx_string_put(s->mlx, s->win_menu, 200, 250, BLACK, "Light on");
// else
// 	mlx_string_put(s->mlx, s->win_menu, 200, 250, BLACK, "Light off");
// draw_radio(s, (t_circle){30, 300, 20, BLACK}, NO_ARGS, false);
