/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:52:39 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/12 17:28:32 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool	setup_menu(t_minirt *s)
{
	s->win_menu = mlx_new_window(s->mlx, MW, MH, MENU_NAME);
	if (s->win_menu == NULL)
		return (false);
	s->menu.img.image = mlx_new_image(s->mlx, MW, MH);
	s->menu.img.height = MH;
	s->menu.img.width = MW;
	if (s->menu.img.image == NULL)
		return (false);
	s->menu.img.data = mlx_get_data_addr(s->menu.img.image, &s->menu.img.bpp,
			&s->menu.img.size_line, &s->menu.img.type);
	if (s->menu.img.data == 0)
		return (false);
	s->menu.radio_one = true;
	s->menu.radio_two = true;
	s->menu.radio_three = true;
	// todo check click spam still needed
	s->menu.click_spam = false;
	s->menu.objects = s->scene.objects;
	return (true);
}

//! TODO watch out for vscode test
bool	setup_assets(t_minirt *s)
{
	if (!load_assets(s))
	{
		ft_dprintf(2, "Asset missing\n");
		return (false);
	}
	s->assets.bt_render.sprite = true;
	s->assets.bt_render.x_grid = s->assets.bt_render.img.width;
	s->assets.bt_render.y_grid = 54;
	s->assets.label_figures.sprite = true;
	s->assets.label_figures.x_grid = s->assets.label_figures.img.width;
	s->assets.label_figures.y_grid = 64;
	s->assets.label_materials.sprite = true;
	s->assets.label_materials.x_grid = s->assets.label_materials.img.width;
	s->assets.label_materials.y_grid = 64;
	return (true);
}

bool	load_assets(t_minirt *s)
{
	if (getenv("TERM_PROGRAM") != NULL)		//we are in vscode
	{
		if (!load_image_asset(s, &s->assets.bt_clrpick,
				"./assets/color_picker_sqr.xpm") ||
			!load_image_asset(s, &s->assets.bt_render,
				"./assets/button_render_ext.xpm") ||
				// "./assets/button_render.xpm") ||
			!load_image_asset(s, &s->assets.label_figures,
				"./assets/figures_ext.xpm") ||
			!load_image_asset(s, &s->assets.label_materials,
				"./assets/materials_ext.xpm") ||
			!load_image_asset(s, &s->assets.bt_gradient,
					"./assets/gradient.xpm") ||
			!load_image_asset(s, &s->assets.ic_al,
				"./assets/ambient_l.xpm") ||
			!load_image_asset(s, &s->assets.ic_pl,
				"./assets/point_l.xpm") ||
			!load_image_asset(s, &s->assets.ic_sl,
				"./assets/spot_l.xpm"))
		return (false);
	}
	else
	{
		if (!load_image_asset(s, &s->assets.bt_clrpick,
				"srcs//assets/color_picker_sqr.xpm") ||
			// !load_image_asset(s, &s->assets.bt_render,
			// 	"srcs//assets/button_render.xpm") ||
			!load_image_asset(s, &s->assets.bt_render,
				"srcs//assets/button_render_ext.xpm") ||
			!load_image_asset(s, &s->assets.label_figures,
				"srcs//assets/figures_ext.xpm") ||
			!load_image_asset(s, &s->assets.label_materials,
				"srcs//assets/materials_ext.xpm") ||
			!load_image_asset(s, &s->assets.bt_gradient,
					"srcs//assets/gradient.xpm") ||
			!load_image_asset(s, &s->assets.ic_al,
				"srcs//assets/ambient_l.xpm") ||
			!load_image_asset(s, &s->assets.ic_pl,
				"srcs//assets/point_l.xpm") ||
			!load_image_asset(s, &s->assets.ic_sl,
				"srcs//assets/spot_l.xpm"))
		return (false);
	}
	return (true);
}
