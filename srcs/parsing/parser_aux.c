/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:12:09 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 12:28:22 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_if_float(char *arg)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (arg[i] != '-' && arg[i] != '+' && !ft_isdigit(arg[i]))
		return (0);
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '.')
			return (0);
		if (arg[i] == '.')
		{
			dot++;
			if (dot > 1)
				return (0);
		}
	}
	return (1);
}

int	check_if_int(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-' && arg[i] != '+' && !ft_isdigit(arg[i]))
		return (0);
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (0);
	return (1);
}

// Check if all minimum elements for the program execution were the file and
// parsed correctly
int	check_needed_elements(t_scene scene, char *file)
{
	if (!scene.cam.has_cam)
		return (ft_dprintf(2, NO_CAMERA, file), 0);
	if (!scene.amb.has_al)
		return (ft_dprintf(2, NO_AMBIENCE, file), 0);
	if (!scene.lights)
		return (ft_dprintf(2, NO_LIGHT, file), 0);
	return (1);
}

// Check if the target is inside given interval
inline int	in_range(float target, float min, float max)
{
	return (target >= min && target <= max);
}
