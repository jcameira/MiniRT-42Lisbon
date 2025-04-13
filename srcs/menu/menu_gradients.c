/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_gradients.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/13 22:33:55 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// gets a value from gradient and returns a normalized float
static float	gradient_picker(t_minirt *p, int x, int y)
{
	int				offset;
	unsigned int	pixel;

	offset = (y * MW + x) * 4;
	pixel = *(unsigned int *)(p->menu.img.data + offset);
	p->menu.gradient_picker = get_rgb(pixel);
	p->menu.gradient_picker.rgb = x;
	return (p->menu.gradient_picker.b / 255.0f);
}

// sets object attribute to found value
static void	set_brightness(t_minirt *p, int x, int y)
{
	t_object		*content;

	content = object_content(p->menu.objects);
	content->mat.br = gradient_picker(p, x, y);
	ft_printf("%sBrightness set to: %s\n", CLEAN, \
		ft_ftoa(content->mat.br, 1000));
}

// sets object attribute to found value
static void	set_fuzz(t_minirt *p, int x, int y)
{
	t_object		*content;

	content = object_content(p->menu.objects);
	content->mat.fuzz = gradient_picker(p, x, y);
	ft_printf("%sFuzz set to: %s\n", CLEAN, \
	ft_ftoa(content->mat.fuzz, 1000));
}

// sets object attribute to found value
static void	set_ri(t_minirt *p, int x, int y)
{
	t_object		*content;

	content = object_content(p->menu.objects);
	content->mat.ri = 4.1 * gradient_picker(p, x, y);
	ft_printf("%sri set to: %s\n", CLEAN, \
	ft_ftoa(content->mat.ri, 1000));
}

void	attribute_picker(t_minirt *p, int x, int y)
{
	if (y >= 226 && y <= 256)
		set_brightness(p, x, y);
	else if (y >= 276 && y <= 306)
		set_fuzz(p, x, y);
	else if (y >= 326 && y <= 356)
		set_ri(p, x, y);
}
