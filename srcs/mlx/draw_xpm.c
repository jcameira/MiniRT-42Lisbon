/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/13 22:40:51 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static bool	verify_xpm_img_data(t_img img, t_img xpm, int x, int y)
{
	if (!img.data || !xpm.data || x < 0 || y < 0
		|| img.height < xpm.height || img.width < xpm.width)
	{
		ft_dprintf(2, "xpm_img defense activated\n");
		return (false);
	}
	return (true);
}

void	join_xpm_sprite(t_img img, t_img_asset xpm, t_coord pos, int idx)
{
	int				i;
	int				j;
	unsigned int	*pix;
	unsigned int	*src;

	if (!verify_xpm_img_data(img, xpm.img, pos.pos[x], pos.pos[y]))
		return ;
	i = -1;
	while (++i < xpm.img.height && i + pos.pos[y] < MH && i < xpm.y_grid)
	{
		pix = (unsigned int *)(img.data + ((((pos.pos[y] + i) * img.width)
						+ pos.pos[x]) << 2));
		src = (unsigned int *)(xpm.img.data
				+ (((i + idx * xpm.y_grid) * xpm.img.width) << 2));
		j = -1;
		while (++j < xpm.img.width && j + pos.pos[x] < MW)
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
		return ;
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

bool	load_image_asset(t_minirt *s, t_img_asset *asset, char *filename)
{
	asset->img.image = mlx_xpm_file_to_image(s->mlx, \
			filename, &asset->img.width, &asset->img.height);
	if (asset->img.image == NULL)
		return (false);
	asset->img.data = mlx_get_data_addr(asset->img.image, \
		&asset->img.bpp, &asset->img.size_line, &asset->img.type);
	if (asset->img.data == NULL)
		return (false);
	asset->sprite = false;
	asset->x_grid = 0;
	asset->y_grid = 0;
	return (true);
}
