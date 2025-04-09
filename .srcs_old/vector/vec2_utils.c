/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:58:28 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 21:14:50 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vec2_copyf(t_rtf result[2], const t_rtf vector[2])
{
	result[0] = vector[0];
	result[1] = vector[1];
}

void	vec2_scalef(t_rtf result[2], const t_rtf vector[2], const t_rtf scalar)
{
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
}

// Calculates the length (magnitude) of a vector
float	vec2_lenf(const t_rtf vector[2])
{
	return (sqrtf(vec2_dotf(vector, vector)));
}
