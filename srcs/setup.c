/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:52:39 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/07 21:08:36 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_rayt, KeyPress, KeyPressMask, &handle_keypress, s);
	mlx_hook(s->win_menu, KeyPress, KeyPressMask, &handle_keypress, s);
	// mlx_hook(s->win_ptr, ButtonPress, ButtonPressMask, &handle_buttons, s);
	mlx_hook(s->win_rayt, DestroyNotify, StructureNotifyMask, &end_minirt, s);
	mlx_mouse_hook(s->win_rayt, mouse_rayt, 0);
	mlx_mouse_hook(s->win_menu, mouse_menu, (void *)s);
	return (0);
}

int	setup_mlx(t_scene scene)
{
	static t_minirt	s;

	s.scene = scene;
	s.mlx = mlx_init();
	if (!s.mlx)
		return (MLX_ERROR);
	// ! do not let this (getenv) go into production
	if (getenv("TERM_PROGRAM") != NULL)	// test for vscode debugging
		s.vscode = true;
	//! end forbidden block
	if (setup_rayt(&s) && setup_assets(&s) && setup_menu(&s) != true)
	{
		free(s.win_rayt);
		free(s.win_menu);
		return (MLX_ERROR);
	}
	s.render = true;
	setup_hooks(&s);
	// minirt(&s);
	// render_menu(&s);
	mlx_loop_hook(s.mlx,minirt, &s);
	mlx_loop(s.mlx);

	return (0);
}

bool	setup_rayt(t_minirt *s)
{
	s->win_rayt = mlx_new_window(s->mlx, W, H, WINDOW_NAME);
	if (s->win_rayt == NULL)
		return (false);
	s->scene.cam.img.image = mlx_new_image(s->mlx, W, H);
	s->scene.cam.img.height = H;
	s->scene.cam.img.width = W;
	s->scene.cam.copy = ft_calloc((W + 32) * H * 4, 1);
	s->scene.cam.red = ft_calloc((W + 32) * H * 4, 1);
	s->scene.cam.cyan = ft_calloc((W + 32) * H * 4, 1);
	s->scene.cam.anaglyph = ft_calloc((W + 32) * H * 4, 1);
	s->scene.cam.clean = ft_calloc((W + 32) * H * 4, 1);
	s->scene.loop = false;
	s->scene.loop_ctr = 0;
	mlx_new_image(s->mlx, W, H);
	if (s->scene.cam.img.image == NULL)
		return (false);
	s->scene.cam.img.data = mlx_get_data_addr(s->scene.cam.img.image, &s->scene.cam.img.bpp,
			&s->scene.cam.img.size_line, &s->scene.cam.img.type);
	if (s->scene.cam.img.data == 0)
		return (false);
	//s->scene.cam.z_buffer = init_zbuffer(H * W);
	return (true);
}

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
	s->menu.background = WHITE;
	// s->menu.color_picker.rgb = YELLOW;
	s->menu.click_spam = false;
	s->menu.objects = s->scene.objects;

	s->assets.label_figures.sprite = true;
	s->assets.label_figures.x_grid = s->assets.label_figures.img.width;
	s->assets.label_figures.y_grid = 64;
	return (true);
}

bool	setup_assets(t_minirt *s)
{
	if (s->vscode)
	{
		if (!load_image_asset(s, &s->assets.bt_clrpick,
				"./assets/color_picker_sqr.xpm") ||
			!load_image_asset(s, &s->assets.bt_render,
				"./assets/button_render.xpm") ||
			!load_image_asset(s, &s->assets.label_figures,
				"./assets/figures_ext.xpm") ||
			!load_image_asset(s, &s->assets.bt_bright,
					"./assets/bright.xpm") ||
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
			!load_image_asset(s, &s->assets.bt_render,
				"srcs//assets/button_render.xpm") ||
			!load_image_asset(s, &s->assets.label_figures,
				"srcs//assets/figures_ext.xpm") ||
			!load_image_asset(s, &s->assets.bt_bright,
					"srcs//assets/bright.xpm") ||
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

bool	load_image_asset(t_minirt *s, t_img_asset *asset, char *filename)
{	if (s->vscode)
		asset->img.image = mlx_xpm_file_to_image(s->mlx,
			filename, &asset->img.width, &asset->img.height);
	else
		asset->img.image = mlx_xpm_file_to_image(s->mlx,
			filename, &asset->img.width, &asset->img.height);
	asset->img.data = mlx_get_data_addr(asset->img.image,
		&asset->img.bpp, &asset->img.size_line, &asset->img.type);
	if (asset->img.image == NULL || asset->img.data == NULL)
		return (false);
	asset->center = false;
	asset->sprite = false;
	asset->x_grid = 0;
	asset->y_grid = 0;
	return (true);
}
