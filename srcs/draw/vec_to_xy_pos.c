/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_xy_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:12:51 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/09 19:04:27 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void world_to_pixel(t_minirt *s, vec3 world_pos, int pixel_coords[2])
{
	vec3 camera_space;
	vec3 temp;
	float ndc_x;
	float ndc_y;

	// 1. Transform to camera space
	vec3_subf(temp, world_pos, s->cam.o);

	// Project onto camera basis vectors
	camera_space[0] = vec3_dotf(temp, s->cam.u);
	camera_space[1] = vec3_dotf(temp, s->cam.v);
	camera_space[2] = -1.0f * vec3_dotf(temp, s->cam.w); // Note z_sign

	// Check if point is behind camera
	if (camera_space[2] <= 0.001f) {
		// Point is behind camera, set to an off-screen position
		pixel_coords[0] = 0;
		pixel_coords[1] = 0;
		return;
	}

	// 2. Calculate viewport projection
	// This follows your camera model in parse_viewport more closely
	float viewport_ratio = camera_space[2] / s->cam.vp.fl;
	ndc_x = camera_space[0] / (viewport_ratio * s->cam.vp.v_width);
	ndc_y = camera_space[1] / (viewport_ratio * s->cam.vp.v_height);

	// 3. Convert to screen coordinates [0,W-1] and [0,H-1]
	pixel_coords[0] = (int)((ndc_x + 1.0f) * (W / 2));
	pixel_coords[1] = (int)((1.0f - ndc_y) * (H / 2));

	// Clamp to viewport bounds
	pixel_coords[0] = clamp(pixel_coords[0], 0, W - 1);
	pixel_coords[1] = clamp(pixel_coords[1], 0, H - 1);
}

void debug_position(t_minirt *s, vec3 world_pos) {
	printf("--- Position Debug ---\n");
	printf("World: (%.2f, %.2f, %.2f)\n", world_pos[0], world_pos[1], world_pos[2]);

	vec3 temp;
	vec3_subf(temp, world_pos, s->cam.o);
	printf("Camera-Relative: (%.2f, %.2f, %.2f)\n", temp[0], temp[1], temp[2]);

	float cam_x = vec3_dotf(temp, s->cam.u);
	float cam_y = vec3_dotf(temp, s->cam.v);
	float cam_z = vec3_dotf(temp, s->cam.w);
	printf("Camera-Space: (%.2f, %.2f, %.2f)\n", cam_x, cam_y, cam_z);

	int coords[2];
	world_to_pixel(s, world_pos, coords);
	printf("Screen: (%d, %d)\n\n", coords[0], coords[1]);
}

void world2_to_pixel(t_minirt *s, vec3 world_pos, int pixel_coords[2])
{
	vec3 camera_space;
	vec3 temp;
	float ndc_x, ndc_y;

	// 1. Transform to camera space
	vec3_subf(temp, world_pos, s->cam.o);

	// Project onto camera basis vectors
	camera_space[0] = vec3_dotf(temp, s->cam.u);
	camera_space[1] = vec3_dotf(temp, s->cam.v);
	camera_space[2] = vec3_dotf(temp, s->cam.w);

	// 2. Apply perspective projection (skip if orthographic)
	// Avoid division by zero with epsilon
	if (fabs(camera_space[2]) < 0.00001f)
		camera_space[2] = 0.00001f;

	// Calculate normalized device coordinates [-1,1]
	ndc_x = camera_space[0] / (camera_space[2] * s->cam.vp.v_width * 0.5f);
	ndc_y = camera_space[1] / (camera_space[2] * s->cam.vp.v_height * 0.5f);

	// 3. Convert to screen coordinates [0,W-1] and [0,H-1]
	pixel_coords[0] = (int)((ndc_x + 1.0f) * (W / 2));
	pixel_coords[1] = (int)((1.0f - ndc_y) * (H / 2));

	// Clamp to viewport bounds
	pixel_coords[0] = (pixel_coords[0] < 0) ? 0 : ((pixel_coords[0] >= W) ? W - 1 : pixel_coords[0]);
	pixel_coords[1] = (pixel_coords[1] < 0) ? 0 : ((pixel_coords[1] >= H) ? H - 1 : pixel_coords[1]);
}
