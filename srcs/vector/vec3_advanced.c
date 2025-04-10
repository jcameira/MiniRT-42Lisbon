/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_advanced.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:34:13 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/09 22:19:51 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Cross Product: vector that is perpendicular to two 3D vectors
void	vec3_crossf(t_rtf result[3], const t_rtf vector0[3],
	const t_rtf vector1[3])
{
	result[0] = vector0[1] * vector1[2] - vector0[2] * vector1[1];
	result[1] = vector0[2] * vector1[0] - vector0[0] * vector1[2];
	result[2] = vector0[0] * vector1[1] - vector0[1] * vector1[0];
}

// Angle Between Vectors: the angle between two 3D vectors.
float	vec3_angle(const float vector0[3], const float vector1[3])
{
	float	dot;
	float	len0;
	float	len1;

	dot = vec3_dotf(vector0, vector1);
	len0 = vec3_lenf(vector0);
	len1 = vec3_lenf(vector1);
	return (acos(dot / (len0 * len1)));
}

// Projection of vector0 onto vector1
// vector0[3]: The vector to be projected.
// vector1[3]: The vector onto which vector0 is projected.
void	vec3_project(t_rtf result[3], const t_rtf vector0[3],
	const t_rtf vector1[3])
{
	float	dot;
	float	len1_sq;
	float	dot_divided_by_len1_sq;

	dot = vec3_dotf(vector0, vector1);
	len1_sq = vec3_dotf(vector1, vector1);
	dot_divided_by_len1_sq = dot / len1_sq;
	result[0] = dot_divided_by_len1_sq * vector1[0];
	result[1] = dot_divided_by_len1_sq * vector1[1];
	result[2] = dot_divided_by_len1_sq * vector1[2];
}
