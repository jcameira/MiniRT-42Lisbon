/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:59:19 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 21:13:24 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vec3_copyf(t_rtf result[3], const t_rtf vector[3])
{
	result[0] = vector[0];
	result[1] = vector[1];
	result[2] = vector[2];
}

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
