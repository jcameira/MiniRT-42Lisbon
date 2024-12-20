/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/20 17:33:18 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minirt.h"

float	*init_zbuffer(size_t size)
{
	float	*z_buffer;

	z_buffer = malloc(size * sizeof(float));
	if (!z_buffer)
		return (NULL);
	ft_memset_float(z_buffer, -FLT_MAX, size);	// new to libft
	return (z_buffer);
}

bool	is_closer(float *z_buffer, float z, int index)
{
	if (z_buffer[index] < z)
	{
		// TODO z_buffer but updates img.data at the same time
		//?	pixel_put	index<<2 color
		z_buffer[index] = z;		//updates buffer
		return (true);
	}
	return (false);
}
