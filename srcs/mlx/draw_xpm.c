/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/04 19:23:38 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static bool	verify_xpm_img_data(t_img img, t_img xpm, int x, int y)
{
	if (!img.data || !xpm.data || x < 0 || y < 0 ||
		img.height < xpm.height || img.width < xpm.width)
	{
		ft_dprintf(2, "xpm_img defense activated\n");
		return (false);
	}
	return (true);
}

void	join_xpm_sprite(t_img img, t_img_asset xpm, int x, int y, int idx)
{
	int				i;
	int				j;
	unsigned int	*pix;
	unsigned int	*src;

	if (!verify_xpm_img_data(img, xpm.img, x, y))
		return;
	i = -1;
	while (++i < xpm.img.height && i + y < MH && i < xpm.y_grid)
	{
		pix = (unsigned int *)(img.data + ((((y + i) * img.width) + x) << 2));
		src = (unsigned int *)(xpm.img.data +
			(((i + idx * xpm.y_grid) * xpm.img.width) << 2));
			// (((i * xpm.img.width) + (idx * xpm.y_grid)) << 2));
		j = -1;
		while (++j < xpm.img.width && j + x < MW)
		{
			if (*src <= 16777215)
				*pix = *src;
			pix++;
			src++;
		}
	}
}

void	join_xpm_img(t_img img, t_img_asset xpm, int x, int y)
{
	int				i;
	int				j;
	unsigned int	*pix;
	unsigned int	*src;

	if (!verify_xpm_img_data(img, xpm.img, x, y))
		return;
	if (xpm.center && !xpm.sprite)
	{
		x = clamp(x - (xpm.img.width / 2), 0, W);
		y = clamp(y - (xpm.img.height / 2), 0, H);
	}
	i = -1;
	while (++i < xpm.img.height && i + y < MH)
	{
		pix = (unsigned int *)(img.data + ((((y + i) * img.width) + x) << 2));
		src = (unsigned int *)(xpm.img.data + ((i * xpm.img.width) << 2));
		j = -1;
		while (++j < xpm.img.width && j + x < MW)
		{
			if (*src <= 16777215)
				*pix = *src;
			pix++;
			src++;
		}
	}
}

// int	get_pixel(t_img *img, int x, int y)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	return (*(unsigned int *)dst);
// }
