/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/02 17:37:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <debug.h>



int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_rt, KeyPress, KeyPressMask, &handle_keypress, s);
	// mlx_hook(s->win_ptr, ButtonPress, ButtonPressMask, &handle_buttons, s);
	mlx_hook(s->win_rt, DestroyNotify, StructureNotifyMask, &end_minirt, s);
	mlx_mouse_hook(s->win_rt, mouse_rt, 0);
	mlx_mouse_hook(s->win_mn, mouse_mn, 0);
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
	s.win_rt = mlx_new_window(s.mlx, W, H, WINDOW_NAME);
	s.win_mn = mlx_new_window(s.mlx, MW, MH, MENU_NAME);
	if (!s.win_rt || !s.win_mn)
	{
		free(s.win_rt);
		free(s.win_mn);
		return (MLX_ERROR);
	}
	s.cam.img.image = mlx_new_image(s.mlx, W, H);
	s.menu.img.image = mlx_new_image(s.mlx, MW, MH);
	s.cam.img.data = mlx_get_data_addr(s.cam.img.image, &s.cam.img.bpp,
			&s.cam.img.size_line, &s.cam.img.type);
	s.menu.img.data = mlx_get_data_addr(s.menu.img.image, &s.menu.img.bpp,
			&s.menu.img.size_line, &s.menu.img.type);

	setup_hooks(&s);
	minirt(&s);
	mlx_loop(s.mlx);
	return (0);
}

int	render(t_minirt *s)
{
	(void)s;
	return (0);
}

int	minirt(t_minirt *s)
{
	render (s);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_camera	cam;

	if (argc != 2)
		return (ft_fprintf(2, NO_ARGS), 1);
	if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))
		|| *(ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) + 3))
		return (ft_fprintf(2, INVALID_RT), 1);
	ft_bzero((void *)&scene, sizeof(scene));
	ft_bzero((void *)&cam, sizeof(cam));
	if (!parser(&scene, &cam, argv[1])
		|| !check_needed_elements(cam, scene, argv[1]))
		return (free_scene(&scene), 1);
	print_parsed_elements(cam, scene);
	setup_mlx(scene, cam);
	return (0);
}
