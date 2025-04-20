/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_quality.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/20 04:40:53 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	quality_list(int idx)
{
	const float	quality[] = {
		0.1,
		1.0,
		3.0,
		40.0};

	return (quality[idx]);
}

void	set_quality(t_minirt *s, int x)
{
	int	idx;

	idx = (int)(x - 40) / 70;
	s->scene.quality = quality_list(idx);
	s->scene.quality_idx = idx;
	print_clean(s);
	ft_printf("number of rays traced %i\n", \
		(int)(RAYS_PER_PIXEL * s->scene.quality));
}
