/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anaglyph_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/13 22:11:53 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Shift camera right (for red eye)
void	create_right_eye(t_minirt *s)
{
	float			original_cam_pos[3];

	ft_memcpy(original_cam_pos, s->scene.cam.o, sizeof(original_cam_pos));
	ft_printf("creating image for right eye (RED)\n");
	s->scene.cam.o[0] += EYE_SEPARATION * s->scene.cam.u[0];
	s->scene.cam.o[1] += EYE_SEPARATION * s->scene.cam.u[1];
	s->scene.cam.o[2] += EYE_SEPARATION * s->scene.cam.u[2];
	calc_viewport_info(&s->scene);
	render_rayt(s);
	dup_image(s->scene.cam.red, s->scene.cam.img.data);
	printf("original viewport info restored\n");
	ft_memcpy(s->scene.cam.o, original_cam_pos, sizeof(original_cam_pos));
}

// Shift camera left from original (for cyan eye)
void	create_left_eye(t_minirt *s)
{
	float			original_cam_pos[3];

	ft_memcpy(original_cam_pos, s->scene.cam.o, sizeof(original_cam_pos));
	ft_printf("creating image for left eye (CYAN)\n");
	s->scene.cam.o[0] -= EYE_SEPARATION * s->scene.cam.u[0];
	s->scene.cam.o[1] -= EYE_SEPARATION * s->scene.cam.u[1];
	s->scene.cam.o[2] -= EYE_SEPARATION * s->scene.cam.u[2];
	calc_viewport_info(&s->scene);
	render_rayt(s);
	dup_image(s->scene.cam.cyan, s->scene.cam.img.data);
	printf("original viewport info restored\n");
	ft_memcpy(s->scene.cam.o, original_cam_pos, sizeof(original_cam_pos));
	calc_viewport_info(&s->scene);
}

// Returns the Dubois right eye matrix value at [row][col]
float	drm(int row, int col)
{
	const float	matrix[3][3] = {
	{-0.043f, -0.088f, -0.002f},
	{0.378f, 0.734f, -0.018f},
	{-0.072f, -0.113f, 1.226f}
	};

	return (matrix[row][col]);
}

// Returns the Dubois left eye matrix value at [row][col]
float	dlm(int row, int col)
{
	const float	matrix[3][3] = {
	{0.456f, 0.500f, 0.176f},
	{-0.040f, -0.038f, -0.016f},
	{-0.015f, -0.021f, -0.005f}
	};

	return (matrix[row][col]);
}
