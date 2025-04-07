/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:23:14 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/07 21:09:17 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	render_rayt(t_minirt *s)
{
	t_pixel	pixel_color;
	t_pixel	temp_color;
	float	pixel_center[3];
	float	ray_direction[3];
	int		iter[3];

	iter[0] = -1;
	while (++iter[0] < H)
	{
		iter[1] = -1;
		while (++iter[1] < W)
		{
			ft_bzero(&pixel_color, sizeof(pixel_color));
			iter[2] = -1;

			// if ((unsigned int *)&s->scene.cam.img[iter[1] * W + iter[0]] != 0)
			// 	continue;
			while (++iter[2] < RAYS_PER_PIXEL)
			{
				pixel_center[x] = s->scene.vp.pixel00l[x] + ((iter[1] + (random_float() - 0.5)) * s->scene.vp.deltah[x]) + ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[x]);
				pixel_center[y] = s->scene.vp.pixel00l[y] + ((iter[1] + (random_float() - 0.5)) * s->scene.vp.deltah[y]) + ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[y]);
				pixel_center[z] = s->scene.vp.pixel00l[z] + ((iter[1] + (random_float() - 0.5)) * s->scene.vp.deltah[z]) + ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[z]);
				//pixel_center[x] = s->scene.vp.pixel00l[x] + (iter[1] * s->scene.vp.deltah[x]) + (iter[0] * s->scene.vp.deltav[x]);
				//pixel_center[y] = s->scene.vp.pixel00l[y] + (iter[1] * s->scene.vp.deltah[y]) + (iter[0] * s->scene.vp.deltav[y]);
				//pixel_center[z] = s->scene.vp.pixel00l[z] + (iter[1] * s->scene.vp.deltah[z]) + (iter[0] * s->scene.vp.deltav[z]);
				vec3_subf(ray_direction, pixel_center, s->scene.cam.o);
				temp_color = ray_color(&s->scene, get_ray(s->scene.cam.o, ray_direction), 50);
				pixel_color = add_pixel_color(pixel_color, temp_color);
			}
			anti_aliasing_get_color(&pixel_color);
			gamma_correction(&pixel_color);
			pixel_put(&s->scene.cam.img, iter[1], iter[0], pixel_color.rgb);
		}
	}
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
	return (0);
}

int	minirt(t_minirt *s)
{
	static int	loop_counter;

	// loop_counter = 1;
	if (s->render)
	{
		ft_dprintf(1, "Raytracer running loop: %i\r", loop_counter);
		render_rayt(s);
		loop_counter++;
	}
	dup_image(s->scene.cam.copy, s->scene.cam.img.data);
	render_menu(s);
	// while (s->render && i < RAYS?PER?PIXEL)
	// update_buffer();
	return (0);
}

void	setup_minirt(t_scene scene)
{
	setup_mlx(scene);
}

int	main(int argc, char **argv)
{
	t_scene		scene;

	if (argc != 2)
		return (ft_dprintf(2, NO_ARGS), 1);
	if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))
		|| *(ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) + 3))
		return (ft_dprintf(2, INVALID_RT), 1);
	ft_bzero((void *)&scene, sizeof(scene));
	if (!parser(&scene, argv[1])
		|| !check_needed_elements(scene, argv[1]))
		return (free_scene(&scene), 1);
	calc_viewport_info(&scene);
	print_parsed_elements(scene);
	setup_minirt(scene);
	return (0);
}
