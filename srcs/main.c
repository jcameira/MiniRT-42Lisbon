/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/13 10:33:01 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <debug.h>

int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_ptr, KeyPress, KeyPressMask, &handle_keypress, s);
	// mlx_hook(s->win_ptr, ButtonPress, ButtonPressMask, &handle_buttons, s);
	mlx_hook(s->win_ptr, DestroyNotify, StructureNotifyMask, &end_minirt, s);
	return (0);
}

int	setup_mlx(t_scene scene, t_camera cam)
{
	static t_minirt	s;

	s.scene = scene;
	s.cam = cam;
	s.mlx_ptr = mlx_init();
	if (!s.mlx_ptr)
		return (MLX_ERROR);
	s.win_ptr = mlx_new_window(s.mlx_ptr, W, H, WINDOW_NAME);
	if (!s.win_ptr)
	{
		free(s.win_ptr);
		return (MLX_ERROR);
	}
	s.cam.img.image = mlx_new_image(s.mlx_ptr, W, H);
	s.cam.img.data = mlx_get_data_addr(s.cam.img.image, &s.cam.img.bpp,
			&s.cam.img.size_line, &s.cam.img.type);
	setup_hooks(&s);
	minirt(&s);
	mlx_loop(s.mlx_ptr);
	return (0);
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
		color.r = 0.5 * ((surface_normal[0] + 1) * 256);
		color.g = 0.5 * ((surface_normal[1] + 1) * 256);
		color.b = 0.5 * ((surface_normal[2] + 1) * 256);
		color.rgb = color.r << 16 | color.g << 8 | color.b;
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

int	render(t_minirt *s)
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
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->cam.img.image, 0, 0);
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
