/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/09 17:04:26 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//draw a rectangule on img buffer, takes struct with coords, size, and color
int	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			pixel_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

/*
int	render_rect_with_alpha(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	if (rect.color >> 24 != 0)
	{
		while (i < rect.y + rect.height)
		{
			j = rect.x;
			while (j < rect.x + rect.width)
				pixel_put_alpha(img, j++, i, rect.color);
			++i;
		}
	}
	else
	{
		while (i < rect.y + rect.height)
		{
			j = rect.x;
			while (j < rect.x + rect.width)
				pixel_put(img, j++, i, rect.color);
			++i;
		}
	}
	return (0);
}
*/
