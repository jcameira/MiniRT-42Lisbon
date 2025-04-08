/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/08 18:06:14 by cjoao-de         ###   ########.fr       */
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
		s->assets.bt_clrpick.img.width + 4, s->assets.bt_clrpick.img.height + 4, GREEN};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){MW - 320, 10, 300, 20, object_content(s->menu.objects)->mat.c.rgb};
	render_rect(&s->menu.img, rect);
	join_xpm_img(s->menu.img, s->assets.bt_clrpick, \
		MW - s->assets.bt_clrpick.img.width - 30, 40);
}

static void	draw_brightness_picker(t_minirt *s)
{
	t_rect	rect;
	int		x_pos;
	// rect = (t_rect){MW - 322, 8, 304, 24, GREEN};
	// render_rect(&s->menu.img, rect);

	// todo interactive color display from figure
	// rect = (t_rect){MW - 320, 10, 300, 20, s->menu.color_picker.rgb};
	// render_rect(&s->menu.img, rect);
	rect = (t_rect){38, 276, \
		s->assets.bt_bright.img.width + 4, s->assets.bt_bright.img.height + 4, GREEN};
		render_rect(&s->menu.img, rect);
		join_xpm_img(s->menu.img, s->assets.bt_bright, 40, 278);

	x_pos = (int)(object_content(s->menu.objects)->mat.br
		* s->assets.bt_bright.img.width) + 40;
	// ft_printf("xpos %i, %s\n", x_pos,
		// ft_ftoa(object_content(s->menu.objects)->mat.br,10000));
	rect = (t_rect){x_pos, 278, 2, 40, CYAN};
	// rect = (t_rect){s->menu.brightness_picker.rgb, 278, 1, 40, RED};
	render_rect(&s->menu.img, rect);
}

int	render_menu(t_minirt *s)
{
	// t_rect	rect;

	set_bk_color(s->menu.img.data, WHITE, MW * MH * 4);
	draw_color_picker(s);
	draw_brightness_picker(s);

	//? figure color changed here
	join_xpm_img(s->menu.img, s->assets.bt_render, (MW - s->assets.bt_render.img.width) / 2, 360);
	join_xpm_sprite(s->menu.img, s->assets.label_figures, 40, 40, object_type(s->menu.objects));
	join_xpm_sprite(s->menu.img, s->assets.label_materials, 40, 134, object_material(s->menu.objects).type - 1);

	mlx_put_image_to_window(s->mlx, s->win_menu, s->menu.img.image, 0, 0);
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
