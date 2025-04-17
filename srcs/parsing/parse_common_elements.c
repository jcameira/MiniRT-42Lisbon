/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:12:09 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 15:35:12 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// General parsing function for a camera that sets the information for its
// origin point, a 3D normalized vector, and its fov that should be in the
// interval of [0, 180]
// It also checks if a camera was already found and parsed in the given file
// since each file should only have at most one camera element
int	parse_cam(t_scene *scene, char *line)
{
	char	**info;

	if (scene->cam.has_cam)
		return (ft_dprintf(2, MULTIPLE_CAMERAS), 0);
	info = ft_split(line, ' ');
	if (!info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(info) != 4)
		return (ft_dprintf(2, CAMERA_USAGE), free_arr((void **)info), 0);
	if (!parse_point(&scene->cam.o, info[1], 0))
		return (ft_dprintf(2, CAMERA_USAGE), free_arr((void **)info), 0);
	if (!parse_point(&scene->cam.nv, info[2], 0))
		return (ft_dprintf(2, CAMERA_USAGE), free_arr((void **)info), 0);
	if (!check_if_float(info[3]))
		return (ft_dprintf(2, CAMERA_USAGE), free_arr((void **)info), 0);
	scene->cam.fov = ft_atoi(info[3]);
	if (!in_range((float)scene->cam.fov, (float)FOV_MIN, (float)FOV_MAX))
		return (ft_dprintf(2, FOV_ERROR), free_arr((void **)info), 0);
	cam_prepare_vp(scene);
	return (free_arr((void **)info), 1);
}

// General parsing function for the ambient light that sets the information
// for its brithness that should be in the interval of [0.0, 1.0] and its color
// It also checks if an ambient light was already found and parsed in the given
// file since each file should only have at most one ambient light element
int	parse_ambience(t_scene *scene, char *line)
{
	char	**info;

	if (scene->amb.has_al)
		return (ft_dprintf(2, MULTIPLE_AMBIENCE), 0);
	info = ft_split(line, ' ');
	if (!info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(info) != 3)
		return (ft_dprintf(2, AMBIENCE_USAGE),
			free_arr((void **)info), 0);
	if (!check_if_float(info[1]))
		return (ft_dprintf(2, AMBIENCE_USAGE),
			free_arr((void **)info), 0);
	scene->amb.al_br = ft_atof(info[1]);
	if (!in_range(scene->amb.al_br, BR_MIN, BR_MAX))
		return (ft_dprintf(2, AMBIENCE_USAGE),
			free_arr((void **)info), 0);
	if (!parse_color(&scene->amb.al_c, info[2]))
		return (ft_dprintf(2, AMBIENCE_USAGE),
			free_arr((void **)info), 0);
	scene->amb.has_al = 1;
	return (free_arr((void **)info), 1);
}
