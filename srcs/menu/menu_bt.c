/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/11 18:03:00 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	render_bt(t_minirt *p)
{
	toogle_bool(&p->render);
	if (p->render == false)
	{
		ft_printf("\n%s\n", "render finished");
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
