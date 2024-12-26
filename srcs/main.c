/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/25 19:17:08 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <debug.h>

float	random_float(void)
{
	return ((float)rand() / RAND_MAX);
}

float	random_float_in_interval(float min, float max)
{
	return (min + ((max - min) * random_float()));
}

t_ray	get_ray(float origin[3], float direction[3])
{
	t_ray	ray;

	vec3_copyf(ray.o, origin);
	vec3_copyf(ray.dir, direction);
	return (ray);
}

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

void	set_face_normal(float ray_direction[3], t_hitrecord *hit_info)
{
	hit_info->front_face = vec3_dotf(ray_direction, hit_info->normal) < 0;
	if(!hit_info->front_face)
		vec3_scalef(hit_info->normal, hit_info->normal, -1);
}

int	hit_sphere(t_ray *ray, float ray_max, t_hitrecord *hit_info, t_figure *tmp)
{
	float	oc[3];
	float	a;
	float	h;
	float	c;
	float	root;

	vec3_subf(oc, tmp->f.sp.c, ray->o);
	a = vec3_dotf(ray->dir, ray->dir);
	h = vec3_dotf(ray->dir, oc);
	c = vec3_dotf(oc, oc) -  (tmp->f.sp.r * tmp->f.sp.r);
	if ((h * h) - (a * c) < 0)
		return (0);
	root = (h - sqrt((h * h) - (a * c))) /  a;
	if (root <= 0.001 || root >= ray_max)
	{
		root = (h + sqrt((h * h) - (a * c))) /  a;
		if (root <= 0.001 || root >= ray_max)
			return (0);
	}
	hit_info->t = root;
	vec3_scalef(ray->dir, ray->dir, root);
	vec3_addf(hit_info->p, ray->o, ray->dir);
	vec3_subf(hit_info->normal, hit_info->p, tmp->f.sp.c);
	vec3_scalef(hit_info->normal, hit_info->normal, (1.0 / tmp->f.sp.r));
	vec3_scalef(ray->dir, ray->dir, 1.0 / root);
	set_face_normal(ray->dir, hit_info);
	return (1);
}

int	find_hittable(t_minirt *s, t_ray *ray, float ray_max, t_hitrecord *hit_info)
{
	t_figure	*tmp;
	float		closest;
	int			hit;

	closest = ray_max;
	hit = 0;
	tmp = s->scene.figures;
	while (tmp)
	{
		if ((tmp->type == SP && hit_sphere(ray, closest, hit_info, tmp)))
		{
			hit = 1;
			closest = hit_info->t;
			hit_info->attenuation = tmp->c;
		}
		tmp = tmp->next;
	}
	return (hit);
}

t_pixel	mult_color(t_pixel color, t_pixel attenuation)
{
	color.r *= (float)attenuation.r / 255;
	color.g *= (float)attenuation.g / 255;
	color.b *= (float)attenuation.b / 255;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}

void	random_on_hemisphere(float new_direction[3], float normal[3])
{
	float	random_unit_vec[3];
	float	len;

	while (true)
	{
		random_unit_vec[x] = random_float_in_interval(-1.0, 1.0);
		random_unit_vec[y] = random_float_in_interval(-1.0, 1.0);
		random_unit_vec[z] = random_float_in_interval(-1.0, 1.0);
		len = vec3_lenf(random_unit_vec);
		if (len > 1e-160 && len <= 1)
		{
			vec3_scalef(random_unit_vec, random_unit_vec, 1 / sqrt(len));
			break ;
		}
	}
	if (vec3_dotf(random_unit_vec, normal) > 0.0)
		vec3_copyf(new_direction, random_unit_vec);
	else
		vec3_scalef(new_direction, random_unit_vec, -1);
}

t_pixel	color(float r, float g, float b)
{
	t_pixel	color;

	color.r = 255 * r;
	color.g = 255 * g;
	color.b = 255 * b;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}

t_pixel	ray_color(t_minirt *s, t_ray ray, int depth)
{
	float		normalized_direction[3];
	float		new_direction[3];
	float		a;
	t_pixel		p_color;
	t_hitrecord	hit_info;

	if (depth <= 0)
		return (color(0, 0, 0));
	if (find_hittable(s, &ray, INFINITY, &hit_info))
	{
		random_on_hemisphere(new_direction, hit_info.normal);
		vec3_addf(new_direction, new_direction, hit_info.normal);
		if (fabs(new_direction[x]) < 1e-8 && fabs(new_direction[y]) < 1e-8 && fabs(new_direction[z]) < 1e-8)
			vec3_copyf(new_direction, hit_info.normal);
		return (mult_color(ray_color(s, get_ray(hit_info.p, new_direction), depth - 1), hit_info.attenuation));
	}
	vec3_copyf(normalized_direction, ray.dir);
	vec3_normalizef(normalized_direction);
	a = 0.5 * (normalized_direction[y] + 1);
	p_color.r = (1 - a) * 255 +  a * 127;
	p_color.g = (1 - a) * 255 +  a * 179;
	p_color.b = (1 - a) * 255 +  a * 255;
	p_color.rgb = p_color.r << 16 | p_color.g << 8 | p_color.b;
	return (p_color);
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

void	gamma_correction(t_pixel *color)
{
	color->r = 255 * sqrt((float)color->r / 255);
	color->g = 255 * sqrt((float)color->g / 255);
	color->b = 255 * sqrt((float)color->b / 255);
	color->rgb = color->r << 16 | color->g << 8 | color->b;
}

int	render(t_minirt *s)
{
	t_pixel pixel_color;
	t_pixel temp_color;
    float pixel_center[3];
    float ray_direction[3];

	for (int j = 0; j < H; j++) {
        for (int i = 0; i < W; i++) {
			ft_bzero(&pixel_color, sizeof(pixel_color));
			for (int sample = 0; sample < 10; sample++){
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
			get_real_color(&pixel_color);
			gamma_correction(&pixel_color);
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
	if (!ft_strnstr(argv[y], ".rt", ft_strlen(argv[y]))
		|| *(ft_strnstr(argv[y], ".rt", ft_strlen(argv[y])) + 3))
		return (ft_fprintf(2, INVALID_RT), 1);
	ft_bzero((void *)&scene, sizeof(scene));
	ft_bzero((void *)&cam, sizeof(cam));
	if (!parser(&scene, &cam, argv[y])
		|| !check_needed_elements(cam, scene, argv[y]))
		return (free_scene(&scene), 1);
	print_parsed_elements(cam, scene);
	setup_mlx(scene, cam);
	return (0);
}
