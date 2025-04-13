/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/13 22:54:45 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	change_material(t_list *object, int type, t_obj_scatter	scatter, \
	float br)
{
	t_object	*content;

	content = object_content(object);
	content->mat.type = type;
	if (br != 2.0 && content->mat.br == 0.0)
		content->mat.br = br;
	if (scatter != NULL)
		content->mat.scatter = scatter;
}

void	set_material(t_list *object, int keysym)
{
	if (keysym == XK_1)
	{
		change_material(object, 1, lambertian_scatter, 2.0);
		ft_printf("Lambertian\n");
	}
	else if (keysym == XK_2)
	{
		change_material(object, 2, specular_scatter, 2.0);
		ft_printf("Specular\n");
	}
	else if (keysym == XK_3)
	{
		change_material(object, 3, dialetric_scatter, 2.0);
		ft_printf("Dialetric\n");
	}
	else if (keysym == XK_4)
	{
		//TODO check with jcameira if no scatter is OK
		change_material(object, 4, NULL, 1);
		ft_printf("Light ON\n");
	}
}
