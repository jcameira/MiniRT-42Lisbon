/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/12 14:22:48 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	render_menu(t_minirt *s)
{
	t_rect	rect;
	// void	*xpm;
	// t_img	xpm_img;
	// int x;
	// int y;

	set_bk_color(s->menu.img.data, YELLOW, MW * MH * 4);
	rect = (t_rect){8, 8, 304, 24, BLACK};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){10, 10, 300, 20, s->menu.color_picker.rgb};
	render_rect(&s->menu.img, rect);
	//? figure color changed here
	// s->scene.figures->c = s->menu.color_picker;
	mlx_put_image_to_window(s->mlx, s->win_menu, s->menu.img.image, 0, 0);
	join_xpm_img(s->menu.img, s->menu.asset1, 20, 40);
	// join_xpm_img(s->menu.img, s->menu.bt_render, 93, 360);
	join_xpm_img(s->menu.img, s->menu.bt_render, (MW-s->menu.bt_render.width) / 2, 360);
	// mlx_put_image_to_window(s->mlx, s->win_menu, s->menu.asset1.image, 20, 40);
	// draw_circle(s->menu.img, (t_circle){110, 500, 20, BLACK});
	// draw_circle_fill(s->menu.img, (t_circle){110, 500, 13, GREEN});
	// mlx_string_put(s->mlx, s->win_menu, 120, 500, BLACK, NO_ARGS);
	// mlx_set_font(s->mlx, s->win_menu, FONT_A);
	draw_radio(s, (t_circle){30, 500, 20, BLACK}, "<- Click ME", s->menu.radio_one);
	// draw_radio(s, (t_circle){30, 300, 20, BLACK}, NO_ARGS, false);
	return (0);
}

void	clear_rayt(t_minirt *s)
{
	set_bk_color(s->scene.cam.img.data, CYAN, W * H * 4);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
}
