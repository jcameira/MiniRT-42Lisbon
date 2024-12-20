/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/20 17:24:22 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <debug.h>

float	random_float(void)
{
	return ((float)rand() / RAND_MAX);
}

int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_rayt, KeyPress, KeyPressMask, &handle_keypress, s);
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
	s->cam.z_buffer = init_zbuffer(H * W);
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
	s->menu.radio_one = true;
	s->menu.background = WHITE;
	return (true);
}

void	set_face_normal(float ray_direction[3], t_hitrecord *hit_info)
{
	hit_info->front_face = vec3_dotf(ray_direction, hit_info->normal) < 0;
	if(!hit_info->front_face)
		vec3_scalef(hit_info->normal, hit_info->normal, -1);
}

int	hit_sphere(t_minirt *s, float ray_direction[3], float ray_max, t_hitrecord *hit_info, t_figure *tmp)
{
	float	oc[3];
	float	a;
	float	h;
	float	c;
	float	root;

	vec3_subf(oc, tmp->f.sp.c, s->cam.o);
	a = vec3_dotf(ray_direction, ray_direction);
	h = vec3_dotf(ray_direction, oc);
	c = vec3_dotf(oc, oc) -  (tmp->f.sp.r * tmp->f.sp.r);
	if ((h * h) - (a * c) < 0)
		return (0);
	root = (h - sqrt((h * h) - (a * c))) /  a;
	if (root <= 0 || root >= ray_max)
	{
		root = (h + sqrt((h * h) - (a * c))) /  a;
		if (root <= 0 || root >= ray_max)
			return (0);
	}
	hit_info->t = root;
	vec3_scalef(ray_direction, ray_direction, root);
	vec3_addf(hit_info->p, s->cam.o, ray_direction);
	vec3_subf(hit_info->normal, hit_info->p, tmp->f.sp.c);
	vec3_scalef(hit_info->normal, hit_info->normal, (1.0 / tmp->f.sp.r));
	vec3_scalef(ray_direction, ray_direction, 1.0 / root);
	set_face_normal(ray_direction, hit_info);
	return (1);
}

int	find_hittable(t_minirt *s, float ray_direction[3], float ray_max, t_hitrecord *hit_info)
{
	t_figure	*tmp;
	float		closest;
	int			hit;

	closest = ray_max;
	hit = 0;
	tmp = s->scene.figures;
	while (tmp)
	{
		if (tmp->type == SP && hit_sphere(s, ray_direction, closest, hit_info, tmp))
		{
			hit = 1;
			closest = hit_info->t;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_pixel	mult_color(t_pixel color, float mult)
{
	color.r *= mult;
	color.g *= mult;
	color.b *= mult;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}

void	random_on_hemisphere(float new_direction[3], float normal[3])
{
	float	random_unit_vec[3];
	float	len;

	while (true)
	{
		random_unit_vec[x] = random_float();
		random_unit_vec[y] = random_float();
		random_unit_vec[z] = random_float();
		vec3_normalizef(random_unit_vec);
		len = vec3_lenf(random_unit_vec);
		if (len > 1e-160 && len <= 1)
		{
			vec3_scalef(random_unit_vec, random_unit_vec, 1 / sqrt(len));
			break ;
		}
	}
	if (vec3_dotf(random_unit_vec, normal) > 0.0)
		vec3_scalef(new_direction, random_unit_vec, -1);
	else
		vec3_copyf(new_direction, random_unit_vec);

}

t_pixel	ray_color(t_minirt *s, float ray_direction[3])
{
	float		normalized_direction[3];
	float		new_direction[3];
	float		a;
	t_pixel		color;
	t_hitrecord	hit_info;

	if (find_hittable(s, ray_direction, INFINITY, &hit_info))
	{
		random_on_hemisphere(new_direction, hit_info.normal);
		return (mult_color(ray_color(s, new_direction), 0.5));
	}
	vec3_copyf(normalized_direction, ray_direction);
	vec3_normalizef(normalized_direction);
	a = 0.5 * (normalized_direction[y] + 1);
	color.r = (1 - a) * 255 +  a * 127;
	color.g = (1 - a) * 255 +  a * 179;
	color.b = (1 - a) * 255 +  a * 255;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}

void add_pixel_color(t_pixel *real_p, t_pixel to_add)
{
	real_p->r += to_add.r;
	real_p->g += to_add.g;
	real_p->b += to_add.b;
	real_p->rgb = real_p->r << 16 | real_p->g << 8 | real_p->b;
}

void get_real_color(t_pixel *real_p)
{
	real_p->r /= 10;
	real_p->g /= 10;
	real_p->b /= 10;
	real_p->rgb = real_p->r << 16 | real_p->g << 8 | real_p->b;
}

int	render(t_minirt *s)
{
	t_pixel pixel_color;
	t_pixel temp_color;

	for (int j = 0; j < H; j++) {
        for (int i = 0; i < W; i++) {
			ft_bzero(&pixel_color, sizeof(pixel_color));
			for (int sample = 0; sample < 10; sample++){
            	float pixel_center[3];
				pixel_center[x] = s->cam.vp.pixel00l[x] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[x]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[x]);
				pixel_center[y] = s->cam.vp.pixel00l[y] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[y]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[y]);
				pixel_center[z] = s->cam.vp.pixel00l[z] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[z]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[z]);
				//pixel_center[x] = s->cam.vp.pixel00l[x] + (i * s->cam.vp.deltah[x]) + (j * s->cam.vp.deltav[x]);
				//pixel_center[y] = s->cam.vp.pixel00l[y] + (i * s->cam.vp.deltah[y]) + (j * s->cam.vp.deltav[y]);
				//pixel_center[z] = s->cam.vp.pixel00l[z] + (i * s->cam.vp.deltah[z]) + (j * s->cam.vp.deltav[z]);
            	float ray_direction[3];
				vec3_subf(ray_direction, pixel_center, s->cam.o);

            	temp_color = ray_color(s, ray_direction);
				add_pixel_color(&pixel_color, temp_color);
			}
			get_real_color(&pixel_color);
            pixel_put(&s->cam.img, i, j, pixel_color.rgb);
        }
    }
	//draw_obb(s, (t_sphere){{1.0, 1.0, 1.0}, 2.0}, BLACK);
	draw_obb(s, s->scene.figures->f.sp, BLACK);
	draw_line(s, (int[2]){20, 20}, (int[2]){50, 50}, BLACK);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
	is_closer(s->cam.z_buffer,s->cam.vp.pixel00l[0], 5);
	return (0);
}

int	render_menu(t_minirt *s)
{
	set_bk_color(s->menu.img.data, YELLOW, MW * MH * 4);

	mlx_put_image_to_window(s->mlx, s->win_menu, s->menu.img.image, 0, 0);
	// draw_circle(s->menu.img, (t_circle){110, 500, 20, BLACK});
	// draw_circle_fill(s->menu.img, (t_circle){110, 500, 13, GREEN});
	// mlx_string_put(s->mlx, s->win_menu, 120, 500, BLACK, NO_ARGS);
	mlx_set_font(s->mlx, s->win_menu, FONT_A);
	draw_radio(s, (t_circle){30, 400, 20, BLACK}, "<- Click ME", s->menu.radio_one);
	// draw_radio(s, (t_circle){30, 300, 20, BLACK}, NO_ARGS, false);
	return (0);
}

void	clear_rayt(t_minirt *s)
{
	// fill_img(s->cam.img.data, WHITE, (W * H) * 4);
	set_bk_color(s->cam.img.data, WHITE, W * H * 4);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
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
	if (!ft_strnstr(argv[y], ".rt", ft_strlen(argv[y]))
		|| *(ft_strnstr(argv[y], ".rt", ft_strlen(argv[y])) + 3))
		return (ft_fprintf(2, INVALID_RT), 1);
	ft_bzero((void *)&scene, sizeof(scene));
	ft_bzero((void *)&cam, sizeof(cam));
	if (!parser(&scene, &cam, argv[y])
		|| !check_needed_elements(cam, scene, argv[y]))
		return (free_scene(&scene), 1);
	//print_parsed_elements(cam, scene);
	setup_mlx(scene, cam);
	return (0);
}
