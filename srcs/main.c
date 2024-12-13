/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/13 17:56:58 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <debug.h>

int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_rayt, KeyPress, KeyPressMask, &handle_keypress, s);
	// mlx_hook(s->win_ptr, ButtonPress, ButtonPressMask, &handle_buttons, s);
	mlx_hook(s->win_rayt, DestroyNotify, StructureNotifyMask, &end_minirt, s);
	mlx_mouse_hook(s->win_rayt, mouse_rt, 0);
	mlx_mouse_hook(s->win_menu, mouse_mn, 0);
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
	if (setup_rayt(&s) && setup_menu(&s) != true)
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
	if (s->cam.img.image == NULL)
		return (false);
	s->cam.img.data = mlx_get_data_addr(s->cam.img.image, &s->cam.img.bpp,
			&s->cam.img.size_line, &s->cam.img.type);
	if (s->cam.img.data == 0)
		return (false);
	return (true);
}

bool	setup_menu(t_minirt *s)
{
	s->win_menu = mlx_new_window(s->mlx, MW, MH, MENU_NAME);
	if (s->win_menu == NULL)
		return (false);
	s->menu.img.image = mlx_new_image(s->mlx, MW, MH);
	if (s->menu.img.image == NULL)
		return (false);
	s->menu.img.data = mlx_get_data_addr(s->menu.img.image, &s->menu.img.bpp,
			&s->menu.img.size_line, &s->menu.img.type);
	if (s->menu.img.data == 0)
		return (false);
	return (true);
}

float	hit_sphere(t_minirt *s, float ray_direction[3])
{
	float	oc[3];
	float	a;
	float	h;
	float	c;
	float	discriminant;

	vec3_subf(oc, s->scene.figures->f.sp.c, s->cam.o);
	a = vec3_dotf(ray_direction, ray_direction);
	h = vec3_dotf(ray_direction, oc);
	c = vec3_dotf(oc, oc) -  (s->scene.figures->f.sp.r * s->scene.figures->f.sp.r);
	discriminant = (h * h) - (a * c);
	if (discriminant < 0)
		return (-1);
	return ((h - sqrt(discriminant)) /  a);
}

t_pixel	ray_color(t_minirt *s, float ray_direction[3])
{
	float	normalized_direction[3];
	float	surface_point[3];
	float	surface_normal[3];
	float	a;
	float	t;
	t_pixel	color;

	t = hit_sphere(s, ray_direction);
	if (t > 0)
	{
		vec3_scalef(ray_direction, ray_direction, t);
		vec3_addf(surface_point, s->cam.o, ray_direction);
		vec3_subf(surface_normal, surface_point, s->scene.figures->f.sp.c);
		rgb_color(&color, surface_normal);
		return (color);
	}
	vec3_copyf(normalized_direction, ray_direction);
	vec3_normalizef(normalized_direction);
	a = 0.5 * (normalized_direction[1] + 1);
	color.r = (1 - a) * 255 +  a * 127;
	color.g = (1 - a) * 255 +  a * 179;
	color.b = (1 - a) * 255 +  a * 255;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}

int	render_rayt(t_minirt *s)
{
	for (int j = 0; j < H; j++) {
		for (int i = 0; i < W; i++) {
			float pixel_center[3];
			pixel_center[0] = s->cam.vp.pixel00l[0] + (i * s->cam.vp.deltah[0]) + (j * s->cam.vp.deltav[0]);
			pixel_center[1] = s->cam.vp.pixel00l[1] + (i * s->cam.vp.deltah[1]) + (j * s->cam.vp.deltav[1]);
			pixel_center[2] = s->cam.vp.pixel00l[2] + (i * s->cam.vp.deltah[2]) + (j * s->cam.vp.deltav[2]);
			float ray_direction[3];
			vec3_subf(ray_direction, pixel_center, s->cam.o);

			t_pixel pixel_color = ray_color(s, ray_direction);
			pixel_put(&s->cam.img, i, j, pixel_color.rgb);
		}
	}
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
	return (0);
}

int	render_menu(t_minirt *s)
{
	fill_img(s->menu.img.data, WHITE, MW * MH * 4);
	draw_radio(s, (t_circle){30, 400, 20, BLACK}, NO_ARGS, true);
	draw_circle(s->menu.img, (t_circle){110, 500, 20, BLACK});
	draw_circle_fill(s->menu.img, (t_circle){110, 500, 13, GREEN});
	// todo pk nao funciona o string_put
	mlx_put_image_to_window(s->mlx, s->win_menu, s->menu.img.image, 0, 0);
	mlx_string_put(s->mlx, s->win_menu, 120, 5
	00, BLACK, NO_ARGS);
	return (0);
}

int	minirt(t_minirt *s)
{
	render_rayt(s);
	render_menu(s);
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
