/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:52:39 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/10 20:57:23 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_rayt, KeyPress, KeyPressMask, &handle_keypress, s);
	mlx_hook(s->win_menu, KeyPress, KeyPressMask, &handle_keypress, s);
	mlx_hook(s->win_rayt, DestroyNotify, StructureNotifyMask, &end_minirt, s);
	// mlx_mouse_hook(s->win_rayt, mouse_rayt, 0);
	mlx_mouse_hook(s->win_menu, menu_mouse, (void *)s);
	return (0);
}

int	setup_mlx(t_scene scene)
{
	static t_minirt	s;

	s.scene = scene;
	s.mlx = mlx_init();
	if (!s.mlx)
		return (MLX_ERROR);
	if (setup_rayt(&s) && setup_assets(&s) && setup_menu(&s) != true)
	{
		free(s.win_rayt);
		free(s.win_menu);
		return (MLX_ERROR);
	}
	// s.render = true;
	s.render = false;
	s.scene.quality = 1.0;
	s.scene.quality_idx = 1;
	setup_hooks(&s);
	// minirt(&s);
	render_menu(&s);
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
	if (!s->scene.cam.copy || !s->scene.cam.red || !s->scene.cam.cyan \
		|| !s->scene.cam.anaglyph || !s->scene.cam.clean \
		||	s->scene.cam.img.image == NULL)
		return (false);
	s->scene.cam.img.data = mlx_get_data_addr(s->scene.cam.img.image, \
		&s->scene.cam.img.bpp, &s->scene.cam.img.size_line, \
		&s->scene.cam.img.type);
	if (s->scene.cam.img.data == 0)
		return (false);
	s->scene.loop = false;
	s->scene.loop_ctr = 0;
	//s->scene.cam.z_buffer = init_zbuffer(H * W);
	return (true);
}
