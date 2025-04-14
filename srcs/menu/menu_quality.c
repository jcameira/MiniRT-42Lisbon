/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_quality.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/14 17:23:39 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	quality_list(int idx)
{
	const float	quality[] = {
		0.1,
		1.0,
		2.5,
		5.0};

	return (quality[idx]);
}

void	set_quality(t_minirt *s, int x)
{
	int	idx;

	idx = (int)(x - 40) / 70;
	s->scene.quality = quality_list(idx);
	s->scene.quality_idx = idx;
	ft_printf("%snumber of rays traced %i\n", CLEAN,
		(int)(RAYS_PER_PIXEL * s->scene.quality));
}
