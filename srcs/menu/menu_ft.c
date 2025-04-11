/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/11 15:18:30 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static float	gradient_picker(t_minirt *p, int x, int y)
{
	// t_object		*content;
	int				offset;
	unsigned int	color;

	offset = (y * MW + x) * 4;
	color = *(unsigned int *)(p->menu.img.data + offset);
	// content = object_content(p->menu.objects);
	p->menu.gradient_picker = get_rgb(color);
	// content->mat.br = p->menu.gradient_picker.b / 255.0f;
	p->menu.gradient_picker.rgb = x;
	// ft_printf("%sBrightness set to: %s\n", CLEAN, \
		// ft_ftoa(object_content(p->menu.objects)->mat.br,1000));
	return (p->menu.gradient_picker.b / 255.0f);
}

// gets and sets, a color from color grid
void	color_picker(t_minirt *p, int x, int y)
{
	t_object		*content;
	int				offset;
	unsigned int	color;

	offset = (y * MW + x) * 4;
	color = *(unsigned int *)(p->menu.img.data + offset);
	p->menu.color_picker = get_rgb(color);
	content = object_content(p->menu.objects);
	content->mat.c = p->menu.color_picker;
	p->menu.color_picker.rgb = color;
	printf("%sColor set to: R-%d G-%d B-%d\n", CLEAN, \
		p->menu.color_picker.r, p->menu.color_picker.g, p->menu.color_picker.g);
}

// gets a value from gradient and sets object brightness
void	brightness_picker(t_minirt *p, int x, int y)
{
	t_object		*content;
	// int				offset;
	// unsigned int	color;

	// offset = (y * MW + x) * 4;
	// color = *(unsigned int *)(p->menu.img.data + offset);
	content = object_content(p->menu.objects);
	// p->menu.gradient_picker = get_rgb(color);
	content->mat.br = gradient_picker(p, x, y);
	// p->menu.gradient_picker.rgb = x;
	ft_printf("%sBrightness set to: %s\n", CLEAN, \
		ft_ftoa(content->mat.br,1000));
}

// gets a value from gradient and sets object brightness
// void	brightness_picker(t_minirt *p, int x, int y)
// {
// 	t_object		*content;
// 	int				offset;
// 	unsigned int	color;

// 	offset = (y * MW + x) * 4;
// 	color = *(unsigned int *)(p->menu.img.data + offset);
// 	content = object_content(p->menu.objects);
// 	p->menu.gradient_picker = get_rgb(color);
// 	content->mat.br = p->menu.gradient_picker.b / 255.0f;
// 	p->menu.gradient_picker.rgb = x;
// 	ft_printf("%sBrightness set to: %s\n", CLEAN, \
// 		ft_ftoa(object_content(p->menu.objects)->mat.br,1000));
// }
