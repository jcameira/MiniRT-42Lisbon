/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:59:19 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/14 09:55:12 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vec3_copyf(t_rtf result[3], const t_rtf vector[3])
{
	result[0] = vector[0];
	result[1] = vector[1];
	result[2] = vector[2];
}

// void	vec4_copyi(int result[4], const int vector[4])
// {
// 	result[0] = vector[0];
// 	result[1] = vector[1];
// 	result[2] = vector[2];
// 	result[3] = vector[4];
// }

void	vec3_scalef(t_rtf result[3], const t_rtf vector[3], const t_rtf scalar)
{
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
	result[2] = vector[2] * scalar;
}

// Calculates the length (magnitude) of a vector
float	vec3_lenf(const t_rtf vector[3])
{
	return (sqrtf(vec3_dotf(vector, vector)));
}

bool	vec3_near_zerof(const float vector[3])
{
	return (fabs(vector[0]) < EPSILON &&
			fabs(vector[1]) < EPSILON &&
			fabs(vector[2]) < EPSILON);
}

bool	vec3_equal(const t_rtf vector1[3], const t_rtf vector2[3])
{
	return (vector1[0] == vector2[0] && vector1[1] == vector2[1]
		&& vector1[2] == vector2[2]);
}