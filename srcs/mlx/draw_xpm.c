/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/09 19:40:17 by cjoao-de         ###   ########.fr       */
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

void	join_xpm_img(t_img img, t_img xpm, int x, int y, bool center)
{
	int				i;
	int				j;
	unsigned int	*pix;
	unsigned int	*src;

	if (!verify_xpm_img_data(img, xpm, x, y))
		return;
	if (center)
	{
		x = clamp(x - (xpm.width / 2), 0, W);
		y = clamp(y - (xpm.height / 2), 0, H);
	}
	i = -1;
	while (++i < xpm.height)
	{
		j = -1;
		pix = (unsigned int *)(img.data + ((((y + i) * img.width) + x) << 2));
		src = (unsigned int *)(xpm.data + ((i * xpm.width) << 2));
		while (++j < xpm.width)
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
