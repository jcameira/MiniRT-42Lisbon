/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:46:08 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/31 19:16:13 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pixel texture_solid_color(const t_texture *texture, float u, float v, const float p[3])
{
	(void)u;
	(void)v;
	(void)p;
	return (texture->tx.solid);
}

t_pixel texture_checker(const t_texture *texture, float u, float v, const float p[3])
{
	(void)u;
	(void)v;
	double sines = sin(10 * p[0]) * sin(10 * p[1]) * sin(10 * p[2]);
	// return (sines < 0) ? texture->tx.checker.odd : texture->tx.checker.even;
	if (sines < 0)
		return (texture->tx.checker.odd);
	else
		return (texture->tx.checker.even);
}

t_pixel texture_image(const t_texture *texture, float u, float v, const float p[3])
{
	int		i;
	int		j;
	char	*pixel;

	(void)p;
	if (!texture->tx.image.data)
		return (get_rgb(CYAN));
	// Clamp UV coordinates to [0, 1]
	u = fmod(fabs(u), 1.0);
	v = 1.0 - fmod(fabs(v), 1.0); // Flip vertically
	i = (int)(u * (texture->tx.image.width - 1));
	j = (int)(v * (texture->tx.image.height - 1));

	// pixel = &texture->tx.image.data[(j * texture->tx.image.width + i) * texture->image.channels];
	// +1 at end to skip alpha channel
	pixel = &texture->tx.image.data[((j * texture->tx.image.width + i) * 4) + 1];
	return (color(pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0));
	// return ((t_pixel){pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0, 0});
}

// todo jcameira pls review (from raytracingin...)
t_vec3	random_unit_vector(void)
{
	vec3	p;
	float	len;
	float	sqrt_len;
	while (true)
	{
		// auto p = vec3::random(-1,1);
		p[0] = random_float_in_interval(-1.0, 1.0);
		p[1] = random_float_in_interval(-1.0, 1.0);
		p[2] = random_float_in_interval(-1.0, 1.0);
		// auto lensq = p.length_squared();
		len = vec3_lenf(p);
		if (len > 1e-160 && len <= 1)
		{
			sqrt_len = sqrtf(len);
			p[0] /= sqrt_len;
			p[1] /= sqrt_len;
			p[2] /= sqrt_len;
			return ((t_vec3){{ p[0], p[1], p[2] }});
		}
	}
}

// todo jcameira pls review (from raytracingin...)
bool material_scatter(const t_texture *texture, const t_ray *ray_in, \
		const t_hitrecord *rec, t_pixel *attenuation, t_ray *scattered)
{
	float	scatter_direction[3];
	t_vec3	random_vec;

	(void)ray_in;
	// Fetch the texture color based on the material's texture type
	if (texture->type == TEXTURE_SOLID)
		*attenuation = texture_solid_color(texture, rec->u, rec->v, rec->p);
	else if (texture->type == TEXTURE_CHECKER)
		*attenuation = texture_checker(texture, rec->u, rec->v, rec->p);
	else if (texture->type == TEXTURE_IMAGE)
		*attenuation = texture_image(texture, rec->u, rec->v, rec->p);
	else
		*attenuation = get_rgb(WHITE); // Default to white if texture type is invalid

	// Generate a scattered ray (diffuse reflection example)
	random_vec = random_unit_vector();
	vec3_addf(scatter_direction, rec->normal, random_vec.vec);
	// t_vec3 scatter_direction = vec3_addf(scatter_direction, &rec->normal, random_unit_vector());
	if (vec3_near_zerof(scatter_direction))
		vec3_copyf(scatter_direction, rec->normal);
	vec3_copyf(scattered->o, rec->p);
	vec3_copyf(scattered->dir, scatter_direction);
	return true;
}

// todo jcameira pls review (from raytracingin...)
void sphere_get_uv(const float p[3], float *u, float *v)
{
	float phi;
	float theta;

	phi = atan2(p[3], p[0]);
	theta = acos(p[1]);
	*u = (phi + M_PI) / (2 * M_PI);
	*v = theta / M_PI;
}

//? for later
// void quad_get_uv(const t_vec3 *p, const t_vec3 *origin, const t_vec3 *u_vec, const t_vec3 *v_vec, double *u, double *v)
// {
// 	t_vec3 delta = vec3_sub(p, origin);
// 	*u = vec3_dot(&delta, u_vec) / vec3_length(u_vec);
// 	*v = vec3_dot(&delta, v_vec) / vec3_length(v_vec);
// }


t_pixel	ray_color2(t_minirt *s, t_ray ray, int depth)
{
	float		normalized_direction[3];
	float		new_direction[3];
	float		a;
	t_pixel		p_color;
	t_hitrecord	hit_info;

	if (depth <= 0)
		return (color(0, 0, 0));

	// Check for object intersection
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
		// Compute new direction for scattered ray
		random_on_hemisphere(new_direction, hit_info.normal);
		vec3_addf(new_direction, new_direction, hit_info.normal);
		if (fabs(new_direction[x]) < 1e-8 && fabs(new_direction[y]) < 1e-8 && fabs(new_direction[z]) < 1e-8)
			vec3_copyf(new_direction, hit_info.normal);

		// Recursively compute color with attenuation
		return (mult_color(ray_color(s, get_ray(hit_info.p, new_direction), depth - 1), hit_info.attenuation));
	}

	// Background gradient
	vec3_copyf(normalized_direction, ray.dir);
	vec3_normalizef(normalized_direction);
	a = 0.5 * (normalized_direction[y] + 1);
	p_color.r = (1 - a) * 255 +  a * 127;
	p_color.g = (1 - a) * 255 +  a * 179;
	p_color.b = (1 - a) * 255 +  a * 255;
	p_color.rgb = p_color.r << 16 | p_color.g << 8 | p_color.b;
	return (p_color);
}

//Example Scene with Textures
// t_scene *create_scene() {
// 	t_scene *scene = scene_create();

// 	// Ground: Checkerboard texture
// 	t_texture ground_texture;
// 	ground_texture.type = TEXTURE_CHECKER;
// 	ground_texture.checker.even = (t_color){0.2, 0.3, 0.1};
// 	ground_texture.checker.odd = (t_color){0.9, 0.9, 0.9};

// 	t_material ground_material;
// 	ground_material.texture = &ground_texture;

// 	t_sphere ground_sphere;
// 	sphere_init(&ground_sphere, (t_vec3){0, -1000, 0}, 1000, &ground_material);
// 	scene_add_object(scene, OBJ_SPHERE, &ground_sphere);

// 	// Sphere with solid color
// 	t_texture sphere_texture;
// 	sphere_texture.type = TEXTURE_SOLID;
// 	sphere_texture.solid_color = (t_color){0.7, 0.3, 0.3};

// 	t_material sphere_material;
// 	sphere_material.texture = &sphere_texture;

// 	t_sphere sphere;
// 	sphere_init(&sphere, (t_vec3){0, 1, 0}, 1, &sphere_material);
// 	scene_add_object(scene, OBJ_SPHERE, &sphere);

// 	return scene;
// }

//? working copy of
//? t_pixel	ray_color(t_minirt *s, t_ray ray, int depth)
/* t_pixel	ray_color(t_minirt *s, t_ray ray, int depth)
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
} */
