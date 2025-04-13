/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/13 23:09:15 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	render_menu(t_minirt *s)
{
	set_bk_color(s->menu.img.data, WHITE, MW * MH * 4);
	join_xpm_sprite(s->menu.img, s->assets.bt_render, \
		(t_coord){(MW - s->assets.bt_render.img.width) - 80, 350}, s->render);
	join_xpm_sprite(s->menu.img, s->assets.label_figures,
		(t_coord){40, 40}, object_type(s->menu.objects));
	join_xpm_sprite(s->menu.img, s->assets.label_materials,
		(t_coord){40, 134}, object_material(s->menu.objects).type - 1);
	draw_color_picker(s);
	draw_gradients(s);
	draw_gradient_values(s);
	draw_quality_picker(s);
	mlx_put_image_to_window(s->mlx, s->win_menu, s->menu.img.image, 0, 0);
	draw_help(s, 300, 455);
	draw_labels(s, 335, 242);
	draw_radio(s, (t_circle){60, 450, 20, BLACK},
		"Restore", s->menu.radio_one);
	draw_radio(s, (t_circle){60, 500, 20, BLACK},
		"Show Anaglyph", s->menu.radio_three);
	draw_radio(s, (t_circle){60, 550, 20, BLACK},
		"Show Left eye / Right eye", s->menu.radio_two);
	draw_radio(s, (t_circle){60, 600, 20, BLACK},
		"Create Anaglyph", s->menu.radio_four);
	return (0);
}
