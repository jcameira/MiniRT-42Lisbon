/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/20 17:52:06 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// gets and sets, a color from color grid
void	color_picker(t_minirt *p, int x, int y)
{
	t_object		*content;
	int				offset;
	unsigned int	pixel;

	offset = (y * MW + x) * 4;
	pixel = *(unsigned int *)(p->menu.img.data + offset);
	p->menu.color_picker = get_rgb(pixel);
	content = object_content(p->menu.objects);
	content->mat.c = p->menu.color_picker;
	p->menu.color_picker.rgb = pixel;
	print_clean(p);
}
