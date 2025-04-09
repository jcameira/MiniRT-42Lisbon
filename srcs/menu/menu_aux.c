/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/09 21:58:57 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//TODO refactor all enums, choose an order
//todo remove
// char	*f_name(int idx)
// {
// 	const char	*f_names[] = {
// 		"SPhere",
// 		"PLane",
// 		"CYlinder",
// 		"COne",
// 		"QUad",
// 		"TRiangle"
// 		"OBject",
// 		"BBox",
// 		"Light",
// 		NULL};
// 	return ((char *)f_names[idx]);
// }

static char	*f_help(int idx)
{
	const char	*f_help[] = {
		"Click [RENDER] to start/stop raytracer",
		"      It will start a new render",
		"Click [GRAYSCALE GRADIENT] to set light brightness",
		"Click [COLOR PALETTE] to set figure color",
		"press [TAB] for next figure",
		"press [1-6] to change material",
		"Click [RESTORE] to restore image",
		"Ask about the other buttons after evaluation mandatory + bonus",
		NULL};
	return ((char *)f_help[idx]);
}

void	draw_help(t_minirt *s, int x, int y)
{
	int padding;
	int i;

	padding = 0;
	i = 0;
	while (f_help(i) != NULL)
	{
		mlx_string_put(s->mlx, s->win_menu, x, y + padding, BLACK, f_help(i));
		padding += 23;
		i++;
	}
}

void	clear_rayt(t_minirt *s)
{
	set_bk_color(s->scene.cam.img.data, CYAN, W * H * 4);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
}
