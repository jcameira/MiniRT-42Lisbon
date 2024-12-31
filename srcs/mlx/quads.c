/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/31 15:32:14 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// _quad Initialization
void quad_init(t_quad *q, const float _q[3], const float u[3], const float v[3], t_pixel color)
{
	vec3_copyf(q->_q, _q);
	vec3_copyf(q->u, u);
	vec3_copyf(q->v, v);
	q->c = color;

	// Calculate plane normal
	float temp[3];
	vec3_crossf(temp, u, v);			// Store cross product result
	vec3_copyf(q->normal, temp);		// Copy to normal
	vec3_normalizef(q->normal);			// Normalize in place

	// Calculate plane D
	q->_d = vec3_dotf(q->normal, _q);

	// Precompute w for planar coordinates
	float n[3];
	vec3_crossf(n, u, v);
	float n_dot_n = vec3_dotf(n, n);
	if (n_dot_n > EPSILON)			// Prevent division by zero
		vec3_scalef(q->w, n, 1.0 / vec3_dotf(n, n));
	else							// Degenerate quad case
		vec3_copyf(q->w, (float[3]){0, 0, 0});

}

// Ray-plane intersection
bool quad_hit(const t_quad *q, const float ray_origin[3], const float ray_dir[3], float *t_out)
{
	float denom;
	float t;

	denom = vec3_dotf(q->normal, ray_dir);
	if (fabs(denom) < EPSILON)
		return (false);

	t = (q->_d - vec3_dotf(q->normal, ray_origin)) / denom;
	if (t < 0)
		return (false);

	float intersection[3];
	float temp[3];
	vec3_scalef(temp, ray_dir, t);
	vec3_addf(intersection, ray_origin, temp);

	float planar_vec[3];
	vec3_subf(planar_vec, intersection, q->_q);

	float alpha;
	float alpha_temp[3];
	vec3_crossf(alpha_temp, planar_vec, q->v);
	alpha = vec3_dotf(q->w, alpha_temp);

	float beta;
	float beta_temp[3];
	vec3_crossf(beta_temp, q->u, planar_vec);
	beta = vec3_dotf(q->w, beta_temp);

	if ((alpha >= 0 && alpha <= 1) && (beta >= 0 && beta <= 1))
	{
		*t_out = t;
		return true;
	}

	return false;
}

// Example usage
bool quad_test(void)
{
	t_quad	q;
	float	t;
	float	_q[3] = {0, 0, 0};
	float	u[3] = {1, 0, 0};
	float	v[3] = {0, 1, 0};

	bool success = true;
	quad_init(&q, _q, u, v, get_rgb(CYAN));
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
