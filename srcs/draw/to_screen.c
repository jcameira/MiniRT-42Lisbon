/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:12:51 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/13 01:11:55 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

typedef struct {
	double x, y, z;
} Vec3;

typedef struct {
	Vec3 eye;       // Camera position
	Vec3 look_at;   // Look-at point
	Vec3 up;        // Up direction
	double fov;     // Field of view in degrees
	double aspect;  // Aspect ratio (width / height)
	int width;      // Screen width in pixels
	int height;     // Screen height in pixels
} Camera;


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



// // Helper function: Subtract two vectors
// Vec3 vec_sub(Vec3 a, Vec3 b) {
// 	return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
// }

// Helper function: Normalize a vector
// Vec3 vec_normalize(Vec3 v)
// {
// 	double len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

// 	return (Vec3){v.x / len, v.y / len, v.z / len};
// }

// Helper function: Cross product of two vectors
// Vec3 vec_cross(Vec3 a, Vec3 b) {
// 	return (Vec3){
// 		.x = a.y * b.z - a.z * b.y,
// 		.y = a.z * b.x - a.x * b.z,
// 		.z = a.x * b.y - a.y * b.x};
// }

// Helper function: Dot product of two vectors
// double vec_dot(Vec3 a, Vec3 b) {
// 	return a.x * b.x + a.y * b.y + a.z * b.z;
// }
