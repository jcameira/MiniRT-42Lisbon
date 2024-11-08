/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:47:38 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/11/08 13:46:39 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// offset is always 4, (bits_per_pixel / 8) == 32 bit RGB / 8 bits == 4 (bytes)
// void	pixel_put(t_img *img, int x, int y, int color)
// {
	// char	*pixel;

	// if (img == NULL || img->data == NULL)
	// {
	// 	fprintf(stderr, "Error: img or img->data is NULL\n");
	// 	return;
	// }
	// Check if x and y are within bounds
	// if (x < 0 || x >= img->width || y < 0 || y >= img->height)
	// {
	//     fprintf(stderr, "Error: x or y is out of bounds\n");
	//     return;
	// }
	// pixel = img->data + (y * img->size_line + x * 4);
	// *(unsigned int *)pixel = color;
// }

// offset is always 4, (bits_per_pixel / 8) == 32 bit RGB / 8 bits == 4 (bytes)
// void	pixel_put(t_img *img, int x, int y, int color)
void	pixel_put(t_img img, int x, int y, int color)
{
	char	*pixel;

	// pixel = img->image->data + (y * img->size_line + x * 4);
	pixel = img.data + (y * img.size_line + x * 4);
	*(unsigned int *)pixel = color;
}

void	pixel_put_alpha(t_img *img, int x, int y, int color)
{
	char	*pixel;
	float	alpha;
	t_pixel	rgb;
	int		c_rgb;

	pixel = img->data + (y * img->size_line + x * 4);
	if (color >> 24 != 0)
	{
		alpha = color >> 24;
		rgb.r = alpha * ((color >> 16) & 0xFF) + (alpha / 255) * pixel[1];
		rgb.g = alpha * ((color >> 8) & 0xFF) - (alpha / 255) * pixel[2];
		rgb.b = alpha * (color & 0xFF) - (alpha / 255) * pixel[3];
		c_rgb = (rgb.r << 16) | (rgb.g << 8) | rgb.b;
		*(unsigned int *)pixel = c_rgb;
		return ;
	}
	*(unsigned int *)pixel = color;
}

// int	render_rect(t_img *img, t_rect rect)
// {
// 	int	i;
// 	int	j;

// 	i = rect.y;
// 	if (rect.color >> 24 != 0)
// 	{
// 		while (i < rect.y + rect.height)
// 		{
// 			j = rect.x;
// 			while (j < rect.x + rect.width)
// 				pixel_put_alpha(img, j++, i, rect.color);
// 			++i;
// 		}
// 	}
// 	else
// 	{
// 		while (i < rect.y + rect.height)
// 		{
// 			j = rect.x;
// 			while (j < rect.x + rect.width)
// 				pixel_put(img, j++, i, rect.color);
// 			++i;
// 		}
// 	}
// 	return (0);
// }
