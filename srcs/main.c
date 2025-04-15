/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:23:14 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/15 16:35:25 by jcameira         ###   ########.fr       */
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
			while (++iter[2] < (int)(RAYS_PER_PIXEL * s->scene.quality))
			{
				pixel_center[x] = s->scene.vp.pixel00l[x] + ((iter[1] + (random_float() - 0.5)) * s->scene.vp.deltah[x]) + ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[x]);
				pixel_center[y] = s->scene.vp.pixel00l[y] + ((iter[1] + (random_float() - 0.5)) * s->scene.vp.deltah[y]) + ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[y]);
				pixel_center[z] = s->scene.vp.pixel00l[z] + ((iter[1] + (random_float() - 0.5)) * s->scene.vp.deltah[z]) + ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[z]);
				vec3_subf(ray_direction, pixel_center, s->scene.cam.o);
				temp_color = ray_color(&s->scene, get_ray(s->scene.cam.o, ray_direction), 50);
				pixel_color = add_pixel_color(pixel_color, temp_color);
			}
			anti_aliasing_get_color(&pixel_color, RAYS_PER_PIXEL * s->scene.quality);
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

	if (loop_counter == 0)
		mlx_string_put(s->mlx, s->win_rayt, H / 2, W / 2, WHITE, \
			"M O V E   T H I S   W I N D O W");
	if (s->render)
	{
		ft_dprintf(1, "Raytracer running loop: %i\r", loop_counter);
		render_rayt(s);
		dup_image(s->scene.cam.copy, s->scene.cam.img.data);
		loop_counter++;
	}
	return (0);
}

void	setup_minirt(char **argv)
{
	static t_minirt	s;
	t_scene		scene;
	ft_bzero((void *)&s, sizeof(t_minirt));
	ft_bzero((void *)&scene, sizeof(scene));
	s.scene = scene;
	s.mlx = mlx_init();
	if (!s.mlx)
		end_minirt(&s);
	if (!parser(&s.scene, argv[1])
		|| !check_needed_elements(s.scene, argv[1]))
		end_minirt(&s);
	calc_viewport_info(&s.scene);
	print_parsed_elements(s.scene);
	if (!(setup_menu(&s) && setup_assets(&s) && setup_rayt(&s)))
		end_minirt(&s);
	s.render = false;
	s.scene.quality = 1.0;
	s.scene.quality_idx = 1;
	setup_hooks(&s);
	mlx_loop_hook(s.mlx, minirt, &s);
	render_menu(&s);
	mlx_loop(s.mlx);
}

//TODO esc does not exit imediatly, problem?
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_dprintf(2, NO_ARGS), 1);
	if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))
		|| *(ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) + 3))
		return (ft_dprintf(2, INVALID_RT), 1);
	setup_minirt(argv);
	return (0);
}
