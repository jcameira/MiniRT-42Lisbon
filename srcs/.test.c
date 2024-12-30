/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/30 06:07:22 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minirt.h"
#include "../lib/libft/include/libft.h"

int	main(void)
{
	char	*pos;
	char	*zero;
	char	*neg;
	char	*negneg;

	pos = "1.100a2";
	zero = "0.00a00";
	neg = "-0.45a6";
	negneg = "-5.0a48";
	printf("%f\n", ft_atof(pos));
	printf("%f\n", ft_atof(zero));
	printf("%f\n", ft_atof(neg));
	printf("%f\n", ft_atof(negneg));
	return (0);
}

////////////////////////////////////
#ifndef QUAD_H
#define QUAD_H

#include "vec3.h"
#include "ray.h"
#include "hittable.h"

typedef struct {
    vec3 Q;
    vec3 u, v;   // Edge vectors
    vec3 normal; // Normal of the plane
    vec3 w;      // Precomputed vector for planar coordinates
    double D;    // Plane equation constant
    color material_color;
} quad;

// Utility function to initialize a quad
void quad_init(quad *q, const vec3 *Q, const vec3 *u, const vec3 *v, color material_color) {
    q->Q = *Q;
    q->u = *u;
    q->v = *v;
    q->material_color = material_color;

    q->normal = vec3_unit(&vec3_cross(u, v));
    q->D = vec3_dot(&q->normal, Q);

    vec3 n = vec3_cross(u, v);
    double n_dot_n = vec3_dot(&n, &n);
    if (n_dot_n > EPSILON) {
        q->w = vec3_mul(&n, 1.0 / n_dot_n);
    } else {
        q->w = (vec3){0, 0, 0};
    }
}

// Ray-Quad intersection
bool quad_hit(const quad *q, const ray *r, double t_min, double t_max, hit_record *rec) {
    double denom = vec3_dot(&q->normal, &r->direction);
    if (fabs(denom) < EPSILON) return false;

    double t = (q->D - vec3_dot(&q->normal, &r->origin)) / denom;
    if (t < t_min || t > t_max) return false;

    vec3 intersection = ray_at(r, t);
    vec3 planar_vec = vec3_sub(&intersection, &q->Q);

    double alpha = vec3_dot(&q->w, &vec3_cross(&planar_vec, &q->v));
    double beta = vec3_dot(&q->w, &vec3_cross(&q->u, &planar_vec));

    if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1) {
        rec->t = t;
        rec->p = intersection;
        rec->normal = q->normal;
        rec->color = q->material_color;
        return true;
    }

    return false;
}
#endif



//////////////////////////////////
#include "quad.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "ray.h"
#include "color.h"

int main() {
    // Image
    const int image_width = 400;
    const int image_height = 200;
    const int samples_per_pixel = 100;

    // World
    hittable_list world;
    hittable_list_init(&world);

    // Add a ground sphere
    sphere ground;
    sphere_init(&ground, (vec3){0, -100.5, -1}, 100.0, (color){0.8, 0.8, 0.0});
    hittable_list_add(&world, (hittable *)&ground);

    // Add a quad
    quad q;
    quad_init(&q, &(vec3){-0.5, 0, -1}, &(vec3){1, 0, 0}, &(vec3){0, 1, 0}, (color){0.1, 0.2, 0.5});
    hittable_list_add(&world, (hittable *)&q);

    // Camera
    camera cam;
    camera_init(&cam, (vec3){3, 3, 2}, (vec3){0, 0, -1}, (vec3){0, 1, 0}, 20, double(image_width) / image_height);

    // Render
    printf("P3\n%d %d\n255\n", image_width, image_height);
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixel_color = {0, 0, 0};
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = camera_get_ray(&cam, u, v);
                pixel_color = vec3_add(&pixel_color, &ray_color(&r, &world));
            }
            write_color(stdout, pixel_color, samples_per_pixel);
        }
    }

    return 0;
}


typedef struct {
	double x, y, z;
} vec3;

typedef struct {
	vec3 min, max;
} aabb;
