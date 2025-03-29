/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:57:21 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 21:15:14 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vec3_addf(t_rtf result[3], const t_rtf vector0[3],
	const t_rtf vector1[3])
{
	result[0] = vector0[0] + vector1[0];
	result[1] = vector0[1] + vector1[1];
	result[2] = vector0[2] + vector1[2];
}

void	vec3_subf(t_rtf result[3], const t_rtf vector0[3],
	const t_rtf vector1[3])
{
	result[0] = vector0[0] - vector1[0];
	result[1] = vector0[1] - vector1[1];
	result[2] = vector0[2] - vector1[2];
}

// Dot Product:
// the sum of the products of the corresponding components of two vectors
float	vec3_dotf(const t_rtf vector0[3], const t_rtf vector1[3])
{
	return (vector0[0] * vector1[0] \
			+ vector0[1] * vector1[1] + vector0[2] * vector1[2]);
}

// Normalize: scales a vector to have a magnitude of 1.
bool	vec3_normalizef(t_rtf vector[3])
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
