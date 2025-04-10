/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/10 19:55:12 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	int pad;
	int i;

	pad = 23;
	i = 0;
	while (f_help(i) != NULL)
	{
		mlx_string_put(s->mlx, s->win_menu, x, y + (pad * i), BLACK, f_help(i));
		i++;
	}
}
