/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_menu_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/07 21:18:13 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


void	set_material(t_list *object, int keysym)
{
	t_object	*content;

	content = object_content(object);
	if (keysym == XK_1)
	{
		content->mat.type = 1;
		content->mat.scatter = &lambertian_scatter;
		ft_printf("\n%s\n", "lambertian_scatter");
	}
	if (keysym == XK_2)
	{
		content->mat.type = 2;
		content->mat.scatter = &specular_scatter;
		ft_printf("\n%s\n", "specular_scatter");
	}
	if (keysym == XK_3)
	{
		content->mat.type = 3;
		content->mat.scatter = &dialetric_scatter;
		ft_printf("\n%s\n", "dialetric_scatter");
	}
	if (keysym == XK_4)
	{
		content->mat.type = 4;
		content->mat.br = 1;
		// content->mat.scatter = &dialetric_scatter;
		ft_printf("\n%s\n", "Light ON");
	}
}
