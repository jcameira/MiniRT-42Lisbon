/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_basic_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:55:27 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 21:15:33 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vec2_addf(t_rtf result[2], const t_rtf vector0[2],
	const t_rtf vector1[2])
{
	result[0] = vector0[0] + vector1[0];
	result[1] = vector0[1] + vector1[1];
}

void	vec2_subf(t_rtf result[2], const t_rtf vector0[2],
	const t_rtf vector1[2])
{
	result[0] = vector0[0] - vector1[0];
	result[1] = vector0[1] - vector1[1];
}

// Dot Product:
// the sum of the products of the corresponding components of two vectors
float	vec2_dotf(const t_rtf vector0[2], const t_rtf vector1[2])
{
	return (vector0[0] * vector1[0] + vector0[1] * vector1[1]);
}

// Normalize: scales a vector to have a magnitude of 1.
bool	vec2_normalizef(t_rtf vector[2])
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
