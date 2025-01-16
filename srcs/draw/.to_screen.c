/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .to_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:12:51 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/14 01:09:01 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
alter the function to convert vertices_world into vertices_camera
also using the cam settings
main.c	draw_wireframe.c	init_oob.c	minirt_typedef.h	draw_wireframe.c
Plan

Transform steps:
World space to camera space
Camera space to normalized device coordinates (NDC)
NDC to screen space

Need:
Camera position (cam.o)
Camera orientation vectors (cam.u, cam.v, cam.w)
Viewport parameters
Update init_bbox_pos function
*/

static void transform_to_camera_space(t_minirt *s, float world[3], float camera[3])
{
	float temp[3];

	// Translate to camera origin
	vec3_subf(temp, world, s->cam.o);

	// Transform using camera basis vectors
	camera[0] = vec3_dot(temp, s->cam.u);
	camera[1] = vec3_dot(temp, s->cam.v);
	camera[2] = vec3_dot(temp, s->cam.w);
}

// usage
static void init_bbox_pos(t_bbox *obb, t_minirt *s)
{
	const int patterns[8][3] = {
		{0,0,1}, {1,0,1}, {1,0,0}, {0,0,0},
		{0,1,1}, {1,1,1}, {1,1,0}, {0,1,0}
	};
	float camera_space[3];
	float ndc[3];

	for (int vertex = 0; vertex < 8; vertex++) {
		// Build world vertex
		for (int i = 0; i < 3; i++) {
			obb->vertices_world[vertex][i] = patterns[vertex][i] ?
				obb->max[i] : obb->min[i];
		}

		// Transform to camera space
		transform_to_camera_space(s, obb->vertices_world[vertex], camera_space);

		// Perspective division for NDC
		float w = camera_space[2];
		if (fabsf(w) < EPSILON) w = EPSILON;

		ndc[0] = camera_space[0] / w;
		ndc[1] = camera_space[1] / w;

		// Convert NDC to screen space
		obb->vertices_camera[vertex][0] = project_normalized_x(ndc[0]);
		obb->vertices_camera[vertex][1] = project_normalized_y(ndc[1]);
	}
}

void init_bbox(t_bbox *obb, float min[3], float max[3], t_minirt *s)
{
	// ...existing normalization code...
	init_vertex_list(obb);
	init_bbox_pos(obb, s);  // Pass minirt struct for camera access
}
// typedef struct {
// 	double x, y, z;
// } Vec3;

// typedef struct {
// 	Vec3 eye;       // Camera position
// 	Vec3 look_at;   // Look-at point
// 	Vec3 up;        // Up direction
// 	double fov;     // Field of view in degrees
// 	double aspect;  // Aspect ratio (width / height)
// 	int width;      // Screen width in pixels
// 	int height;     // Screen height in pixels
// } Camera;


// // Function to find screen coordinates of a 3D point
// void world_to_screen(Camera *camera, Vec3 point, int *screen_x, int *screen_y)
// {
// 	// Compute camera basis vectors
// 	Vec3 forward = vec3_normalizef(vec_sub(camera->look_at, camera->eye));
// 	Vec3 right = vec3_normalizef(vec_crossf(forward, camera->up));
// 	Vec3 up = vec3_cross(right, forward);

// 	// Transform point to camera space
// 	Vec3 relative_point = vec3_subf(point, camera->eye);
// 	double camera_x = vec3_dotf(relative_point, right);
// 	double camera_y = vec3_dotf(relative_point, up);
// 	double camera_z = vec3_dotf(relative_point, forward);

// 	// Perspective divide
// 	double fov_scale = tan((camera->fov * M_PI / 180.0) / 2.0);
// 	double ndc_x = (camera_x / (fov_scale * camera_z)) / camera->aspect;
// 	double ndc_y = camera_y / (fov_scale * camera_z);

// 	// Convert to screen coordinates
// 	*screen_x = (int)((ndc_x + 1.0) * 0.5 * camera->width);
// 	*screen_y = (int)((1.0 - ndc_y) * 0.5 * camera->height);
// }

// #include "vec3.h"
// #include "ray.h"
// #include "camera.h" // Assuming the camera is defined similarly in the book

// void world_to_screen(
//     const camera& cam, const point3& point,
//     int image_width, int image_height,
//     int& screen_x, int& screen_y
// ) {
//     // Compute the camera coordinate system
//     auto forward = unit_vector(cam.lookat - cam.lookfrom); // Viewing direction
//     auto right = unit_vector(cross(forward, cam.vup));    // Right direction
//     auto up = cross(right, forward);                      // Up direction

//     // Transform the 3D point to camera space
//     vec3 relative_point = point - cam.lookfrom;
//     double camera_x = dot(relative_point, right);
//     double camera_y = dot(relative_point, up);
//     double camera_z = dot(relative_point, forward);

//     // Perspective projection
//     double aspect_ratio = double(image_width) / image_height;
//     double fov_scale = tan(degrees_to_radians(cam.vfov) / 2.0);
//     double ndc_x = (camera_x / (fov_scale * camera_z)) / aspect_ratio;
//     double ndc_y = camera_y / (fov_scale * camera_z);

//     // Convert to screen coordinates
//     screen_x = static_cast<int>((ndc_x + 1.0) * 0.5 * image_width);
//     screen_y = static_cast<int>((1.0 - ndc_y) * 0.5 * image_height);
// }
