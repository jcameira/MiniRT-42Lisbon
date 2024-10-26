/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:00:46 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/26 20:17:51 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	apply_rotation(float **vec, int angle, t_xyz axis)
{
	static float	rotmat[3][3] = {{0}};

	rotmat[0][0] = cos(angle);
	rotmat[1][1] = cos(angle);
	rotmat[2][2] = cos(angle);
	if (axis == x)
	{
        rotmat[0][0] = 1;
        rotmat[1][2] = -sin(angle);
        rotmat[2][1] = sin(angle);

    }
	else if (axis == y)
	{
        rotmat[0][2] = sin(angle);
        rotmat[1][1] = 1;
        rotmat[2][0] = -sin(angle);
    }
	else if (axis == z)
	{
        rotmat[0][1] = -sin(angle);
        rotmat[1][0] = sin(angle);
        rotmat[2][2] = 1;
    }
	mul_vec_by_mat(vec, (float **)rotmat);
}
