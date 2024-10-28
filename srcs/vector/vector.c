/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:34:13 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/27 20:27:06 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vec3_copyf(t_rtf result[3], const t_rtf vector[3])
{
	result[0] = vector[0];
	result[1] = vector[1];
	result[2] = vector[2];
}

void	vec2_copyf(t_rtf result[2], const t_rtf vector[2])
{
	result[0] = vector[0];
	result[1] = vector[1];
}

void	vec3_addf(t_rtf result[3], const t_rtf vector0[3],
	const t_rtf vector1[3])
{
	result[0] = vector0[0] + vector1[0];
	result[1] = vector0[1] + vector1[1];
	result[2] = vector0[2] + vector1[2];
}

void	vec2_addf(t_rtf result[2], const t_rtf vector0[2],
	const t_rtf vector1[2])
{
	result[0] = vector0[0] + vector1[0];
	result[1] = vector0[1] + vector1[1];
}

void	vec3_subf(t_rtf result[3], const t_rtf vector0[3],
	const t_rtf vector1[3])
{
	result[0] = vector0[0] - vector1[0];
	result[1] = vector0[1] - vector1[1];
	result[2] = vector0[2] - vector1[2];
}

void	vec2_subf(t_rtf result[2], const t_rtf vector0[2],
	const t_rtf vector1[2])
{
	result[0] = vector0[0] - vector1[0];
	result[1] = vector0[1] - vector1[1];
}

// Dot Product:
// the sum of the products of the corresponding components of two vectors
float	vec3_dotf(const t_rtf vector0[3], const t_rtf vector1[3])
{
	return (vector0[0] * vector1[0] \
			+ vector0[1] * vector1[1] + vector0[2] * vector1[2]);
}

// Dot Product:
// the sum of the products of the corresponding components of two vectors
float	vec2_dotf(const t_rtf vector0[2], const t_rtf vector1[2])
{
	return (vector0[0] * vector1[0] + vector0[1] * vector1[1]);
}

void	vec3_scalef(t_rtf result[3], const t_rtf vector[3], const t_rtf scalar)
{
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
	result[2] = vector[2] * scalar;
}

void	vec2_scalef(t_rtf result[2], const t_rtf vector[2], const t_rtf scalar)
{
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
}

// Calculates the length (magnitude) of a vector
float	vec3_lenf(const t_rtf vector[3])
{
	return (sqrtf(vec3_dotf(vector, vector)));
}

// Calculates the length (magnitude) of a vector
float vec2_lenf(const t_rtf vector[2])
{
	return (sqrtf(vec2_dotf(vector, vector)));
}

// Normalize: scales a vector to have a magnitude of 1.
bool vec3_normalizef(t_rtf vector[3])
{
	t_rtf	length;

	length = vec3_lenf(vector);
	if (length == 0.0f)
	{
		return (false);
	}
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	return (true);
}

// Normalize: scales a vector to have a magnitude of 1.
bool vec2_normalizef(t_rtf vector[2])
{
	t_rtf	length;

	length = vec2_lenf(vector);
	if (length == 0.0f)
	{
		return (false);
	}
	vector[0] /= length;
	vector[1] /= length;
	return (true);
}
