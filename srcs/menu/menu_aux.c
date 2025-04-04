/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/04 17:04:21 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//TODO refactor all enums, choose an order
char	*f_name(int idx)
{
	const char	*f_names[] = {
		"SPhere",
		"PLane",
		"CYlinder",
		"COne",
		"QUad",
		"TRiangle"
		"OBject",
		"BBox",
		"Light",
		NULL};
	return ((char *)f_names[idx]);
}

void	clear_rayt(t_minirt *s)
{
	set_bk_color(s->scene.cam.img.data, CYAN, W * H * 4);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
}
