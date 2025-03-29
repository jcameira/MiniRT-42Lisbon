/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_random.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:07:00 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/18 09:44:32 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	random_float(void)
{
	return ((float)rand() / (float)RAND_MAX);
}

float	random_float_in_interval(float min, float max)
{
	return (min + ((max - min) * random_float()));
}

int	random_int_in_interval(int min, int max)
{
	return ((int)random_float_in_interval(min, max + 1));
}

void	random_unit_vector(float new_direction[3])
{
	float	random_unit_vec[3];
	float	len;

	while (true)
	{
		random_unit_vec[x] = random_float_in_interval(-1.0, 1.0);
		random_unit_vec[y] = random_float_in_interval(-1.0, 1.0);
		random_unit_vec[z] = random_float_in_interval(-1.0, 1.0);
		len = vec3_dotf(random_unit_vec, random_unit_vec);
		if (len > 1e-160 && len <= 1)
		{
			vec3_scalef(new_direction, random_unit_vec, 1 / sqrt(len));
			break ;
		}
	}
}

void	random_on_hemisphere(float new_direction[3], float normal[3])
{
	float	random_unit_vec[3];

	random_unit_vector(random_unit_vec);
	if (vec3_dotf(random_unit_vec, normal) > 0.0)
		vec3_copyf(new_direction, random_unit_vec);
	else
		vec3_scalef(new_direction, random_unit_vec, -1);
}
