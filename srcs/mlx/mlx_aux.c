/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:47:38 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/13 22:40:11 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// offset is always 4, (bits_per_pixel / 8) == 32 bit RGB / 8 bits == 4 (bytes)
void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + (y * img->size_line + x * 4);
	*(unsigned int *)pixel = color;
}

void	set_bk_color(char *data, int color, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(int *)data = color;
		data += 4;
		i += 4;
	}
}
