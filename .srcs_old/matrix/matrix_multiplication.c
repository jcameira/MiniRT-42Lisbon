/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiplication.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:28:59 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 20:54:36 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Multiplies a given matrix with a given vector and updates the given vector
// with the resulting vector
void	mul_vec_by_mat(float **vec, float **mat)
{
	float	new_vec[3];
	int		i;

	i = -1;
	while (++i < 3)
		new_vec[i] = vec3_dotf(*vec, mat[i]);
	vec3_copyf(*vec, new_vec);
}

// Remove the z value from a vector
void	orthographic(float **vec)
{
	(*vec)[2] = 0;
}
