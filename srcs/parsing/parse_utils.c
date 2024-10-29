/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:13:40 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 20:45:14 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Check if all minimum elements for the program execution were the file and
// parsed correctly
int	check_needed_elements(t_camera cam, t_scene scene, char *file)
{
	if (!cam.has_cam)
		return (ft_fprintf(2, NO_CAMERA, file), 0);
	if (!scene.has_al)
		return (ft_fprintf(2, NO_AMBIENCE, file), 0);
	if (!scene.lights)
		return (ft_fprintf(2, NO_LIGHT, file), 0);
	return (1);
}

// Skip to the beggining of the next piece of information of a given element
void	skip_info(char **line)
{
	while (**line && (ft_isdigit(**line) || **line == '.' || **line == ','
			|| **line == '-'))
		(*line)++;
	while (**line && (!ft_isdigit(**line) && **line != '-'))
		(*line)++;
}

// Check if the target is inside given interval
int	in_range(float target, float min, float max)
{
	return (target >= min && target <= max);
}

// General parsing function for a 3 axis point or 3D normalized vector that
// should be written in the given file exectly as such -> x,y,z
// For a 3D normalized vector the values of x, y and z should be in the
// interval of [-1, 1]
int	parse_point(float (*point)[3], char *line, int vector)
{
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!(*line))
		return (ft_fprintf(2, POINT_ERROR), 0);
	(*point)[x] = ft_atof(line);
	if (vector && !in_range((*point)[x], NV_AXIS_MIN, NV_AXIS_MAX))
		return (ft_fprintf(2, POINT_ERROR), 0);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	if (*line && (*line != ',' || *line + 1 == ','))
		return (ft_fprintf(2, POINT_ERROR), 0);
	line++;
	(*point)[y] = ft_atof(line);
	if (vector && !in_range((*point)[y], NV_AXIS_MIN, NV_AXIS_MAX))
		return (ft_fprintf(2, POINT_ERROR), 0);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	if (*line && (*line != ',' || *line + 1 == ','))
		return (ft_fprintf(2, POINT_ERROR), 0);
	line++;
	(*point)[z] = ft_atof(line);
	if (vector && !in_range((*point)[z], NV_AXIS_MIN, NV_AXIS_MAX))
		return (ft_fprintf(2, POINT_ERROR), 0);
	return (1);
}

// General parsing function for an rgb color that should be written in
// the given file exectly as such -> r,g,b
// Each of the values of r, g and b should be in the interval of [0, 255]
int	parse_color(char *line)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(line);
	if (!in_range((float)r, (float)RGB_MIN, (float)RGB_MAX))
		return (ft_fprintf(2, COLOR_ERROR), -1);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line && (*line != ',' || *line + 1 == ','))
		return (ft_fprintf(2, COLOR_ERROR), -1);
	line++;
	g = ft_atoi(line);
	if (!in_range((float)g, (float)RGB_MIN, (float)RGB_MAX))
		return (ft_fprintf(2, COLOR_ERROR), -1);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line && (*line != ',' || *line + 1 == ','))
		return (ft_fprintf(2, COLOR_ERROR), -1);
	line++;
	b = ft_atoi(line);
	if (!in_range((float)b, (float)RGB_MIN, (float)RGB_MAX))
		return (ft_fprintf(2, COLOR_ERROR), -1);
	return (r << 16 | g << 8 | b);
}
