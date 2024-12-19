/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:31:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/19 21:20:26 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minirt.h"

float	*init_zbuffer(size_t size)
{
	float	*z_buffer;

	z_buffer = ft_calloc(size, sizeof(float));
	return (z_buffer);
}

bool	is_closer(float *z_buffer, float z, int index)
{
	if (z_buffer[index] > z)
		return (true);
	return (false);
}

// TODO z_buffer but updates img.data at the same time
// bool ()
// if is_closer
//	pixel_put
