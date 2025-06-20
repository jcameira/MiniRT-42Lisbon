/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:12:09 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 20:42:39 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// General parsing function for a camera that sets the information for its
// origin point, a 3D normalized vector, and its fov that should be in the
// interval of [0, 180]
// It also checks if a camera was already found and parsed in the given file
// since each file should only have at most one camera element
int	parse_cam(t_camera *cam, char *line)
{
	if (cam->has_cam)
		return (ft_fprintf(2, MULTIPLE_CAMERAS), 0);
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&cam->o, line, 0))
		return (0);
	skip_info(&line);
	if (!parse_point(&cam->nv, line, 1))
		return (0);
	skip_info(&line);
	cam->fov = ft_atoi(line);
	if (!in_range((float)cam->fov, (float)FOV_MIN, (float)FOV_MAX))
		return (ft_fprintf(2, FOV_ERROR), 0);
	cam->has_cam = 1;
	return (1);
}

// General parsing function for the ambient light that sets the information
// for its brithness that should be in the interval of [0.0, 1.0] and its color
// It also checks if an ambient light was already found and parsed in the given
// file since each file should only have at most one ambient light element
int	parse_ambience(t_scene *scene, char *line)
{
	if (scene->has_al)
		return (ft_fprintf(2, MULTIPLE_AMBIENCE), 0);
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!(*line))
		return (ft_fprintf(2, AMBIENCE_USAGE), 0);
	scene->al_br = ft_atof(line);
	if (!in_range(scene->al_br, BR_MIN, BR_MAX))
		return (ft_fprintf(2, AMBIENCE_USAGE), 0);
	skip_info(&line);
	if (!(*line))
		return (ft_fprintf(2, AMBIENCE_USAGE), 0);
	scene->al_c = parse_color(line);
	if (scene->al_c == -1)
		return (ft_fprintf(2, AMBIENCE_USAGE), 0);
	scene->has_al = 1;
	return (1);
}

// General parsing function for the light that sets the information
// for its origine, its brithness that should be in the interval
// of [0.0, 1.0] and its color as well as adding it to the back of
// the light list since the structure of the program is already
// prepared to receive multiple lights in the same given file
int	parse_light(t_scene *scene, char *line)
{
	t_light	*new_l;

	new_l = malloc(sizeof(t_light));
	if (!new_l)
		return (ft_fprintf(2, NO_SPACE), 0);
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&new_l->o, line, 0))
		return (ft_fprintf(2, LIGHT_USAGE), free(new_l), 0);
	skip_info(&line);
	new_l->br = ft_atof(line);
	if (!in_range(new_l->br, BR_MIN, BR_MAX))
		return (ft_fprintf(2, LIGHT_USAGE), 0);
	skip_info(&line);
	new_l->c = parse_color(line);
	if (new_l->c == -1)
		return (ft_fprintf(2, LIGHT_USAGE), free(new_l), 0);
	new_l->next = NULL;
	ft_lstadd_back((t_list **)&scene->lights, (t_list *)new_l);
	return (1);
}
