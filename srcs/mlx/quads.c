/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/29 03:28:35 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

#define EPSILON 1e-8

typedef struct {
	double x, y, z;
} vec3;

typedef struct {
	vec3 min, max;
} aabb;

typedef struct {
	// vec3 Q;     // Starting corner of the quad
	// vec3 u, v;  // Edge vectors
	// vec3 normal, w;  // Plane normal and w vector
	// double D;   // Plane equation constant ////////////////////
	float	Q[3];     // Starting corner of the quad
	float	u[3];
	float	v[3];  // Edge vectors
	float	normal[3];
	float	w[3];  // Plane normal and w vector
	float	D;
} quad;

/*
// Utility functions
vec3 vec3_crossf(const vec3 *a, const vec3 *b) {
	return (vec3){
		a->y * b->z - a->z * b->y,
		a->z * b->x - a->x * b->z,
		a->x * b->y - a->y * b->x
	};
}

double vec3_dotf(const vec3 *a, const vec3 *b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

vec3 vec3_subf(const vec3 *a, const vec3 *b) {
	return (vec3){a->x - b->x, a->y - b->y, a->z - b->z};
}

vec3 vec3_addf(const vec3 *a, const vec3 *b) {
	return (vec3){a->x + b->x, a->y + b->y, a->z + b->z};
}

vec3 vec3_scalef(const vec3 *v, double scalar) {
	return (vec3){v->x * scalar, v->y * scalar, v->z * scalar};
}

vec3 vec3_normalizef(const vec3 *v) {
	double length = sqrt(vec3_dotf
(v, v));
	return vec3_scalef(v, 1.0 / length);
}
 */
// Quad Initialization

// void quad_init(t_plane *q, const vec3 *Q, const vec3 *u, const vec3 *v)
void quad_init(t_plane *q, const float Q[3], const float u[3], const float v[3])
{
	vec3_copyf(q->Q, Q);
	vec3_copyf(q->u, u);
	vec3_copyf(q->v, v);
	// q->Q = *Q;
	// q->u = *u;
	// q->v = *v;

	// Calculate plane normal
	// q->normal = vec3_normalizef(&vec3_crossf(u, v));
	float temp[3];
	vec3_crossf(temp, u, v);        // Store cross product result
	vec3_copyf(q->normal, temp);      // Copy to normal
	vec3_normalizef(q->normal);       // Normalize in place

	// Calculate plane D
	q->D = vec3_dotf(q->normal, Q);

	// Precompute w for planar coordinates
	// vec3 n = vec3_crossf(n, u, v);
	float n[3];
	vec3_crossf(n, u, v);
	// q->w = vec3_scalef(&n, 1.0 / vec3_dotf(&n, &n));
	// float w[3];
	// q->w =
	vec3_scalef(q->w, n, 1.0 / vec3_dotf(n, n));
}

// Ray-plane intersection
bool quad_hit(const t_plane *q, const float ray_origin[3], const float ray_dir[3], float *t_out)
{
	// float denom = vec3_dotf(&q->normal, ray_dir);
	float denom;
	float t;

	denom = vec3_dotf(q->normal, ray_dir);
	if (fabs(denom) < EPSILON)
		return (false);

	t = (q->D - vec3_dotf(q->normal, ray_origin)) / denom;
	if (t < 0)
		return (false);

	// float intersection[3] = vec3_addf(ray_origin, &vec3_scalef(ray_dir, t));
	float intersection[3];
	float temp[3];
	vec3_scalef(temp, ray_dir, t);
	// vec3_addf(intersection, *ray_origin, vec3_scalef(temp, *ray_dir, t));
	vec3_addf(intersection, ray_origin, temp);

	// float planar_vec[3] = vec3_subf(&intersection, &q->Q);
	float planar_vec[3];
	vec3_subf(planar_vec, intersection, q->Q);

	// float alpha = vec3_dotf(&q->w, &vec3_crossf(&planar_vec, &q->v));
	float alpha;
	float alpha_temp[3];
	vec3_crossf(alpha_temp, planar_vec, q->v);
	alpha = vec3_dotf(q->w, alpha_temp);

	// float beta = vec3_dotf(&q->w, &vec3_crossf(&q->u, &planar_vec));
	float beta;
	float beta_temp[3];
	vec3_crossf(beta_temp, q->u, planar_vec);
	beta = vec3_dotf(q->w, beta_temp);

	if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1)
	{
		*t_out = t;
		return true;
	}

	return false;
}

// Example usage
bool plane_test(void)
{
	t_plane	q;
	float	t;
	float	Q[3] = {0, 0, 0};
	float	u[3] = {1, 0, 0};
	float	v[3] = {0, 1, 0};

	bool success = true;
	//void quad_init(t_plane *q, const float *Q[3], const float *u[3],
	// const float *v[3])
	quad_init(&q, Q, u, v);

	// float ray_origin[3] = {0.5, 0.5, -1};
	// float ray_dir[3] = {0, 0, 1};

	// if (quad_hit(&q, &ray_origin, &ray_dir, &t))
	// if (quad_hit(&q, ray_origin, ray_dir, &t))
	// 	printf("Hit! t = %f\n", t);
	// else
	// 	printf("Miss!\n");
	// return 0;
	{
		float ray_origin[3] = {0.5, 0.5, -1};  // Above quad center
		float ray_dir[3] = {0, 0, 1};          // Straight down
		bool hit = quad_hit(&q, ray_origin, ray_dir, &t);
		printf("Test 1 (should hit): %s, t=%f\n", hit ? "PASS" : "FAIL", t);
		success &= hit;
	}

	// Test 2: Ray should miss quad
	{
		float ray_origin[3] = {2, 2, -1};      // Outside quad bounds
		float ray_dir[3] = {0, 0, 1};          // Straight down
		bool hit = quad_hit(&q, ray_origin, ray_dir, &t);
		// printf("Test 2 (should miss): %s\n", !hit ? "PASS" : "FAIL");
		printf("Test 1 (should miss): %s, t=%f\n", !hit ? "PASS" : "FAIL", t);
		success &= !hit;
	}

	return success;

}
