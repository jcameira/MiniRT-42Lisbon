/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_changes_and_merge.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:58:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/04 04:30:16 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//! todo where did come from?
t_pixel	mult_color(t_pixel color, t_pixel attenuation)
{
	color.r *= (float)attenuation.r / 255;
	color.g *= (float)attenuation.g / 255;
	color.b *= (float)attenuation.b / 255;
	color.rgb = color.r << 16 | color.g << 8 | color.b;
	return (color);
}

//todo merge changes
int	find_hittable_old(t_minirt *s, t_ray *ray, float ray_max, t_hitrecord *hit_info)
{
	t_figure	*tmp;
	float		closest;
	int			hit;

	closest = ray_max;
	hit = 0;
	tmp = s->scene.figures;
	float	t;
	while (tmp)
	{

		if (tmp->type == SP && hit_sphere(ray, closest, hit_info, tmp))
		{
			hit = 1;
			closest = hit_info->t;
			hit_info->attenuation = tmp->c;
			hit_info->texture = &tmp->texture;
		}
		else if (tmp->type == QU && quad_hit(&tmp->f.qu, ray->o, ray->dir, &t))
		{
			hit = 1;
			closest = hit_info->t;
			hit_info->attenuation = tmp->c;
			hit_info->texture = &tmp->texture;
			// closest_t = rec.t;
			// hit_anything = true;
			// closest_rec = rec;
		}

		tmp = tmp->next;
	}
	return (hit);
}

//todo merge changes
t_pixel	ray_color_old(t_minirt *s, t_ray ray, int depth)
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
		if (hit_info.texture->type == TEXTURE_SOLID)
			hit_info.attenuation = texture_solid_color(hit_info.texture, hit_info.u, hit_info.v, hit_info.p);
		else if (hit_info.texture->type == TEXTURE_CHECKER)
			hit_info.attenuation = texture_checker(hit_info.texture, hit_info.u, hit_info.v, hit_info.p);
		else if (hit_info.texture->type == TEXTURE_IMAGE)
			hit_info.attenuation = texture_image(hit_info.texture, hit_info.u, hit_info.v, hit_info.p);
		else
			hit_info.attenuation = get_rgb(WHITE); // Default to white if texture type is invalid
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

//todo merge changes into new render_rayt
int	render_rayt_old(t_minirt *s)
{
	t_pixel pixel_color;
	t_pixel temp_color;
	float pixel_center[3];
	float ray_direction[3];

	// // Add a quad
	// t_figure	*new_f;
	// new_f = malloc(sizeof(t_figure));
	// new_f->type = QU;
	// new_f->next = NULL;
	// float	Q[3] = {-1, 0, -1};
	// float	u[3] = {2, 0, 0};
	// float	v[3] = {0, 2, 0};
	// quad_init(&new_f->f.qu, Q, u, v, get_rgb(MAGENTA));
	// ft_lstadd_back((t_list **)&s->scene.figures, (t_list *)new_f);

	for (int j = 0; j < H; j++) {
        for (int i = 0; i < W; i++) {
			ft_bzero(&pixel_color, sizeof(pixel_color));
			for (int sample = 0; sample < 1; sample++){
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

	//draw_obb(s, (t_sphere){{1.0, 1.0, 1.0}, 2.0}, BLACK);
	draw_obb(s, s->scene.figures->f.sp, GREEN);
	draw_line(s, (t_line)
		{{20, 20}, {50, 50}, 0, 0 , 0, 0, 0, NULL, GREEN});
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
	is_closer(s->cam.z_buffer,s->cam.vp.pixel00l[0], 5);
	quad_test();
	printf("click spam\n");
	s->menu.click_spam = false;
	return (0);
}
