/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/10 21:10:33 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	render_bt(t_minirt *p)
{
	toogle_bool(&p->render);
	if (p->render == false)
	{
		ft_printf("%s%s\n", CLEAN, "render finished");
		dup_image(p->scene.cam.copy, p->scene.cam.img.data);
	}
	else
	{
		//new render, clean buffer 1st
		ft_bzero(p->scene.cam.img.data, p->scene.cam.pixels * 4);
		ft_printf("%s\n", "render starting");
	}
}

void	radio_one(t_minirt *p)
{
	if (p->render)
		return ;
	toogle_bool(&p->menu.radio_one);
	ft_printf("%s\n", "render restored");
	restore_image(p, p->scene.cam.copy);
}

void	radio_two(t_minirt *p)
{
	if (p->render)
		return ;
	if (p->menu.radio_two == true)
	{
		toogle_bool(&p->menu.radio_two);
		ft_printf("%s\n", "render red");
		restore_image(p, p->scene.cam.red);
	}
	else
	{
		toogle_bool(&p->menu.radio_two);
		ft_printf("%s\n", "render cyan");
		restore_image(p, p->scene.cam.cyan);
	}
}

void	radio_three(t_minirt *p)
{
	if (p->render)
		return ;
	toogle_bool(&p->menu.radio_three);
	ft_printf("%s\n", "clean");
	// clean(p->scene.cam.clean);
	// restore_image(p, p->scene.cam.clean);
}

void	radio_four(t_minirt *p)
{
	if (p->render)
		return ;
	create_anaglyph(p);
	toogle_bool(&p->menu.radio_four);
	ft_printf("%s\n", "render anaglyph");
	restore_image(p, p->scene.cam.anaglyph);
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
	int				offset;
	unsigned int	color;

	offset = (y * MW + x) * 4;
	color = *(unsigned int *)(p->menu.img.data + offset);
	content = object_content(p->menu.objects);
	p->menu.brightness_picker = get_rgb(color);
	content->mat.br = p->menu.brightness_picker.b / 255.0f;
	p->menu.brightness_picker.rgb = x;
	ft_printf("%sBrightness set to: %s\n", CLEAN, \
		ft_ftoa(object_content(p->menu.objects)->mat.br,1000));
}
