/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:52:39 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/24 18:12:53 by cjoao-de         ###   ########.fr       */
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

int	setup_mlx(t_scene scene, t_camera cam)
{
	static t_minirt	s;

	s.scene = scene;
	s.cam = cam;
	s.mlx = mlx_init();
	if (!s.mlx)
		return (MLX_ERROR);
	// // ! do not let this (getenv) go into production
	if (getenv("TERM_PROGRAM") != NULL)	// test for vscode debugging
		s.vscode = true;
	//? test count_line
	// int fd;
	// if (s.vscode)
	// 	fd = open("././scenes/window_obj.rt", O_RDONLY);	// from debugger
	// else
	// 	fd = open("scenes/window_obj.rt", O_RDONLY); // from terminal
	// if (fd < 0)
	// 	return (ft_dprintf(2, FILE_NOT_FOUND, "window_obj.rt"), 0);
	// printf("lines %i\n", count_lines(fd));	//? end test
	//! end forbidden block
	if (setup_rayt(&s) && setup_menu(&s) && setup_assets(&s) != true)
	{
		free(s.win_rayt);
		free(s.win_menu);
		return (MLX_ERROR);
	}
	setup_hooks(&s);
	minirt(&s);
	mlx_loop(s.mlx);

	return (0);
}

bool	setup_rayt(t_minirt *s)
{
	s->win_rayt = mlx_new_window(s->mlx, W, H, WINDOW_NAME);
	if (s->win_rayt == NULL)
		return (false);
	s->cam.img.image = mlx_new_image(s->mlx, W, H);
	s->cam.img.height = H;
	s->cam.img.width = W;
	s->cam.copy = ft_calloc((W + 32) * H * 4, 1);
	s->cam.red = ft_calloc((W + 32) * H * 4, 1);
	s->cam.cyan = ft_calloc((W + 32) * H * 4, 1);
	s->cam.anaglyph = ft_calloc((W + 32) * H * 4, 1);
	s->cam.clean = ft_calloc((W + 32) * H * 4, 1);
	mlx_new_image(s->mlx, W, H);
	if (s->cam.img.image == NULL)
		return (false);
	s->cam.img.data = mlx_get_data_addr(s->cam.img.image, &s->cam.img.bpp,
			&s->cam.img.size_line, &s->cam.img.type);
	if (s->cam.img.data == 0)
		return (false);
	s->cam.z_buffer = init_zbuffer(H * W);
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
	s->menu.figures = s->scene.figures;

	return (true);
}

bool	setup_assets(t_minirt *s)
{
	if (s->vscode)
	{
		if (!load_image_asset(s, &s->assets.bt_clrpick,
			"./mlx/color_picker_sqr.xpm") ||
			!load_image_asset(s, &s->assets.bt_render,
			"./mlx/button_render.xpm") ||
			!load_image_asset(s, &s->assets.ic_al,
				"./mlx/ambient_l.xpm") ||
			!load_image_asset(s, &s->assets.ic_pl,
				"./mlx/point_l.xpm") ||
			!load_image_asset(s, &s->assets.ic_sl,
				"./mlx/spot_l.xpm"))
		return (false);
	}
	else
	{
		if (!load_image_asset(s, &s->assets.bt_clrpick,
			"srcs//mlx/color_picker_sqr.xpm") ||
			!load_image_asset(s, &s->assets.bt_render,
			"srcs//mlx/button_render.xpm") ||
			!load_image_asset(s, &s->assets.ic_al,
			"srcs//mlx/ambient_l.xpm") ||
			!load_image_asset(s, &s->assets.ic_pl,
			"srcs//mlx/point_l.xpm") ||
			!load_image_asset(s, &s->assets.ic_sl,
			"srcs//mlx/spot_l.xpm"))
		return (false);
	}
	return (true);
}

	// if (s->vscode)
	// 	s->menu.asset1.image = mlx_xpm_file_to_image(s->mlx, "./mlx/color_picker_sqr.xpm", &s->menu.asset1.width, &s->menu.asset1.height);
	// else
	// 	s->menu.asset1.image = mlx_xpm_file_to_image(s->mlx, "srcs/mlx/color_picker_sqr.xpm", &s->menu.asset1.width, &s->menu.asset1.height);
	// s->menu.asset1.data = mlx_get_data_addr(s->menu.asset1.image,
	// 	&s->menu.asset1.bpp, &s->menu.asset1.size_line, &s->menu.asset1.type);
bool	load_image_asset(t_minirt *s, t_img *asset, char *filename)
{	if (s->vscode)
		// asset->image = mlx_xpm_file_to_image(s->mlx,
		// 	"./mlx/color_picker_sqr.xpm",
		// 	&asset->width, &asset->height);
		asset->image = mlx_xpm_file_to_image(s->mlx,
			filename, &asset->width, &asset->height);
	else
		asset->image = mlx_xpm_file_to_image(s->mlx,
			filename, &asset->width, &asset->height);
	asset->data = mlx_get_data_addr(asset->image,
		&asset->bpp, &asset->size_line, &asset->type);
	if (asset->image == NULL || asset->data == NULL)
		return (false);
	return (true);
}
