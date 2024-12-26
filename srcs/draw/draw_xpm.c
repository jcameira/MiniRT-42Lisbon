/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/26 17:52:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	join_xpm_img(t_img img, t_img xpm, int x, int y)
{
	int		i;
	int		j;
	char	*pix;
	char	*src;

	i = 0;
	if (img.height < xpm.height || img.width < xpm.width)
		return ;
	while (i < xpm.height)
	{
		j = 0;
		pix = img.data + (( ((y + i) * img.width) + x + j) << 2);
		src = xpm.data + (( (i * xpm.width) + j) << 2);
		while (j < xpm.width)
		{
			ft_memmove(pix, src, 4);
			// if (*(unsigned char *)(src) != 0)
			// {
			// 	ft_memmove(pix, src, 4);
			// }
			pix += 4;
			src += 4;
			j++;
		}
		i++;
	}
}

// int	get_pixel(t_img *img, int x, int y)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	return (*(unsigned int *)dst);
// }
