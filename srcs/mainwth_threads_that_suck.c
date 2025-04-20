/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:23:14 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/20 19:34:49 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float random_float_threadsafe(unsigned int *seed) {
	// Use a reentrant RNG algorithm like xorshift or use rand_r if available
	// return (seed);
	*seed = rand_r(seed);
	return (*seed / (float)RAND_MAX);
}

void	get_final_color(t_minirt *s, t_pixel *pixel_color, int iter[2])
{
	t_pixel	temp_color;
	float	pixel_center[3];
	float	ray_direction[3];

	pixel_center[x] = s->scene.vp.pixel00l[x]
		+ ((iter[1] + (random_float() - 0.5))
			* s->scene.vp.deltah[x])
		+ ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[x]);
	pixel_center[y] = s->scene.vp.pixel00l[y]
		+ ((iter[1] + (random_float() - 0.5))
			* s->scene.vp.deltah[y])
		+ ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[y]);
	pixel_center[z] = s->scene.vp.pixel00l[z]
		+ ((iter[1] + (random_float() - 0.5))
			* s->scene.vp.deltah[z])
		+ ((iter[0] + (random_float() - 0.5)) * s->scene.vp.deltav[z]);
	vec3_subf(ray_direction, pixel_center, s->scene.cam.o);
	temp_color = ray_color(&s->scene,
			get_ray(s->scene.cam.o, ray_direction), 50);
	*pixel_color = add_pixel_color(*pixel_color, temp_color);
}

void	get_final_color_threadsafe(t_minirt *s, t_pixel *pixel_color,
			int iter[2], unsigned int *seed)
{
	t_pixel	temp_color;
	float	pixel_center[3];
	float	ray_direction[3];

	pixel_center[x] = s->scene.vp.pixel00l[x]
		+ ((iter[1] + (random_float_threadsafe(seed) - 0.5))
			* s->scene.vp.deltah[x])
		+ ((iter[0] + (random_float_threadsafe(seed) - 0.5)) * s->scene.vp.deltav[x]);
	pixel_center[y] = s->scene.vp.pixel00l[y]
		+ ((iter[1] + (random_float_threadsafe(seed) - 0.5))
			* s->scene.vp.deltah[y])
		+ ((iter[0] + (random_float_threadsafe(seed) - 0.5)) * s->scene.vp.deltav[y]);
	pixel_center[z] = s->scene.vp.pixel00l[z]
		+ ((iter[1] + (random_float_threadsafe(seed) - 0.5))
			* s->scene.vp.deltah[z])
		+ ((iter[0] + (random_float_threadsafe(seed) - 0.5)) * s->scene.vp.deltav[z]);
	vec3_subf(ray_direction, pixel_center, s->scene.cam.o);
	temp_color = ray_color(&s->scene,
			get_ray(s->scene.cam.o, ray_direction), 50);
	*pixel_color = add_pixel_color(*pixel_color, temp_color);
}

int	render_rayt(t_minirt *s)
{
	time_t			time;
	unsigned int	*pixel;
	int 			rays = (int)RAYS_PER_PIXEL * s->scene.quality;
	// int				max_threads = omp_get_max_threads();
	int				max_threads = 4;
	 // Get max possible threads
	unsigned	 int	*rng_seeds;
	 // Array to hold seeds for each thread

	time = get_time();
	pixel = (unsigned int *)s->scene.cam.img.data;
	// Allocate and initialize seeds for each potential thread
	rng_seeds = malloc(max_threads * sizeof(unsigned int));
	// if (!rng_seeds) { /* Handle allocation error */ return (1); }
	srand(time); // Seed the main random generator once
	for(int i = 0; i < max_threads; ++i)
		rng_seeds[i] = rand() + i; // Simple unique seed initialization

		// omp_set_num_threads(2);
	#pragma omp parallel for shared(pixel) collapse(2)
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			t_pixel pixel_color;
			int index = i * W + j;
			int thread_id = omp_get_thread_num(); // Get the current thread's ID
			unsigned int *my_seed = &rng_seeds[thread_id]; // Get pointer to this thread's seed
			ft_bzero(&pixel_color, sizeof(pixel_color));
			for (int ray = 0; ray < rays; ray++)
			get_final_color_threadsafe(s, &pixel_color, (int[2]){i, j}, my_seed);
			anti_aliasing_get_color(&pixel_color, rays);
			gamma_correction(&pixel_color);
			pixel[index] = pixel_color.rgb;
		}
	}
	free(rng_seeds); // Free the allocated seeds
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
	return (print_clean(s), print_time(get_time() - time), 0);
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
	t_scene			scene;

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
