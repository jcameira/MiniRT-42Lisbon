/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2025/02/10 19:07:41 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// t_coord project_normalized_vec3(const vec3 vec)
// {
// 	t_coord pos;

// 	// Convert from [-1,1] to  [0,W-1] and [0,H-1]
// 	pos.pos[x] = (int)((vec[x] + 1.0f) * (W / 2));
// 	pos.pos[y] = (int)((1.0f - vec[y]) * (H / 2));

// 	// Clamp to viewport bounds
// 	pos.pos[x] = clamp(pos.pos[x], 0, W - 1);
// 	pos.pos[y] = clamp(pos.pos[y], 0, H - 1);
// 	// pos[x] = (pos[x] < 0) ? 0 : ((pos[x] >= W) ? W - 1 : pos[x]);
// 	// pos[y] = (pos[y] < 0) ? 0 : ((pos[y] >= H) ? H - 1 : pos[y]);
// 	return pos;
// }



int	render_rayt(t_minirt *s)
{
	t_pixel	pixel_color;
	t_pixel	temp_color;
    float	pixel_center[3];
    float	ray_direction[3];

	for (int j = 0; j < H; j++) {
        for (int i = 0; i < W; i++) {
			ft_bzero(&pixel_color, sizeof(pixel_color));
			for (int sample = 0; sample < RAYS_PER_PIXEL; sample++){
				pixel_center[x] = s->cam.vp.pixel00l[x] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[x]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[x]);
				pixel_center[y] = s->cam.vp.pixel00l[y] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[y]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[y]);
				pixel_center[z] = s->cam.vp.pixel00l[z] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[z]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[z]);
				//pixel_center[x] = s->cam.vp.pixel00l[x] + (i * s->cam.vp.deltah[x]) + (j * s->cam.vp.deltav[x]);
				//pixel_center[y] = s->cam.vp.pixel00l[y] + (i * s->cam.vp.deltah[y]) + (j * s->cam.vp.deltav[y]);
				//pixel_center[z] = s->cam.vp.pixel00l[z] + (i * s->cam.vp.deltah[z]) + (j * s->cam.vp.deltav[z]);
				vec3_subf(ray_direction, pixel_center, s->cam.o);
				temp_color = ray_color(s, get_ray(s->cam.o, ray_direction), 50);
				add_pixel_color(&pixel_color, temp_color);
			}
			anti_aliasing_get_color(&pixel_color);
			gamma_correction(&pixel_color);
			pixel_put(&s->cam.img, i, j, pixel_color.rgb);
		}
	}
	// s->menu.click_spam = false;
	dup_image(s->cam.copy, s->cam.img.data);
	// separate(s);c
	// create_left_right(s);
	t_figure *current = s->scene.figures;
	while (current != NULL)
	{
		if (current->type == SP)
		{
			// s->scene.figures->f.sp
			// init_bbox(&s->scene.figures->b, &s->scene.figures->f.sp);
			draw_obb(s, &current->b, GREEN);
		}
		current = current->next;
	}
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
	return (0);
}

int	minirt(t_minirt *s)
{
	render_rayt(s);
	render_menu(s);
	return (0);
}

void	setup_minirt(t_scene scene, t_camera cam)
{
	setup_mlx(scene, cam);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_camera	cam;

	if (argc != 2)
		return (ft_dprintf(2, NO_ARGS), 1);
	if (!ft_strnstr(argv[y], ".rt", ft_strlen(argv[y]))
		|| *(ft_strnstr(argv[y], ".rt", ft_strlen(argv[y])) + 3))
		return (ft_dprintf(2, INVALID_RT), 1);
	ft_bzero((void *)&scene, sizeof(scene));
	ft_bzero((void *)&cam, sizeof(cam));
	if (!parser(&scene, &cam, argv[y])
		|| !check_needed_elements(cam, scene, argv[y]))
		return (free_scene(&scene), 1);
	print_parsed_elements(cam, scene);

		// Add a quad
	//t_figure	*new_f;
	//new_f = malloc(sizeof(t_figure));
	//new_f->type = QU;
	//new_f->next = NULL;
	//float	_q[3] = {-1, 0, -1};
	//float	u[3] = {2, 0, 0};
	//float	v[3] = {0, 2, 0};
	//quad_init(&new_f->f.qu, _q, u, v, get_rgb(MAGENTA));
	//ft_lstadd_back((t_list **)&scene.figures, (t_list *)new_f);
	//printf("Quad normal: (%f, %f, %f)\n", new_f->f.qu.normal[x], new_f->f.qu.normal[y], new_f->f.qu.normal[z]);
	setup_minirt(scene, cam);
	return (0);
}
