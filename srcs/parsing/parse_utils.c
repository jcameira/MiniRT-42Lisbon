/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:13:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/09 20:33:45 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

// Skip to the beggining of the next piece of information of a given element
void	skip_info(char **line)
{
	while (**line && (ft_isdigit(**line) || **line == '.' || **line == ','
			|| **line == '-' || **line == '+'))
		(*line)++;
	while (**line && (!ft_isdigit(**line) && **line != '-' && **line != '+'))
		(*line)++;
}

// Check if the target is inside given interval
inline int	in_range(float target, float min, float max)
{
	return (target >= min && target <= max);
}

// General parsing function for a 3 axis point or 3D normalized vector that
// should be written in the given file exectly as such -> x,y,z
// For a 3D normalized vector the values of x, y and z should be in the
// interval of [-1, 1]
int	parse_point(float (*point)[3], char *line, int vector)
{
	(void) vector;
	while (*line && !ft_isdigit(*line) && *line != '-' && *line != '+')
		line++;
	if (!(*line))
		return (ft_dprintf(2, POINT_ERROR), 0);
	(*point)[x] = ft_atof(line);
	while (*line && (ft_isdigit(*line) || *line == '.'
			|| *line == '-' || *line == '+'))
		line++;
	if (*line && (*line != ',' || *(line + 1) == ','))
		return (ft_dprintf(2, POINT_ERROR), 0);
	line++;
	(*point)[y] = ft_atof(line);
	while (*line && (ft_isdigit(*line) || *line == '.'
			|| *line == '-' || *line == '+'))
		line++;
	if (*line && (*line != ','
			|| (!ft_isdigit(*(line + 1)) && *(line + 1) != '-')))
		return (ft_dprintf(2, POINT_ERROR), 0);
	line++;
	(*point)[z] = ft_atof(line);
	//if (vector && (!in_range((*point)[x], NV_AXIS_MIN, NV_AXIS_MAX)
	//	|| !in_range((*point)[y], NV_AXIS_MIN, NV_AXIS_MAX)
	//	|| !in_range((*point)[z], NV_AXIS_MIN, NV_AXIS_MAX)))
	//	return (ft_dprintf(2, POINT_ERROR), 0);
	return (1);
}

// General parsing function for an rgb color that should be written in
// the given file exectly as such -> r,g,b
// Each of the values of r, g and b should be in the interval of [0, 255]
int	parse_color(t_pixel *c, char *line)
{
	if (!(*line))
		return (ft_dprintf(2, COLOR_ERROR), 0);
	c->r = ft_atoi(line);
	while (*line && (ft_isdigit(*line) || *line == '+'))
		line++;
	if (*line && (*line != ',' || *(line + 1) == ','))
		return (ft_dprintf(2, COLOR_ERROR), 0);
	line++;
	c->g = ft_atoi(line);
	while (*line && (ft_isdigit(*line) || *line == '+'))
		line++;
	if (*line && (*line != ',' || !ft_isdigit(*(line + 1))))
		return (ft_dprintf(2, COLOR_ERROR), 0);
	line++;
	c->b = ft_atoi(line);
	if (!in_range((float)c->r, (float)RGB_MIN, (float)RGB_MAX)
		|| !in_range((float)c->g, (float)RGB_MIN, (float)RGB_MAX)
		|| !in_range((float)c->b, (float)RGB_MIN, (float)RGB_MAX))
		return (ft_dprintf(2, COLOR_ERROR), 0);
	c->rgb = c->r << 16 | c->g << 8 | c->b;
	return (1);
}

int	parse_material(t_material *mat, char *line)
{
	if (!(*line))
	{
		mat->type = 1;
		mat->scatter = &lambertian_scatter;
		mat->fuzz = 0;
		return (1);
	}
	mat->type = ft_atoi(line);
	if (!in_range((float)mat->type, lambertian, emission))
		return (ft_dprintf(2, MATERIAL_ERROR), 0);
	if (mat->type == lambertian)
	{
		mat->scatter = &lambertian_scatter;
		mat->fuzz = 0;
	}
	if (mat->type == metal)
	{
		mat->scatter = &specular_scatter;
		skip_info(&line);
		if (!(*line))
		{
			mat->fuzz = 0;
			return (1);
		}
		mat->fuzz = ft_atof(line);
		if (!in_range(mat->fuzz, 0, 1))
			return (ft_dprintf(2, MATERIAL_ERROR), 0);
	}
	if (mat->type == dialetric)
	{
		mat->scatter = &dialetric_scatter;
		skip_info(&line);
		if (!(*line))
		{
			mat->ri = 0;
			return (1);
		}
		mat->ri = ft_atof(line);
		if (!in_range(mat->ri, 0.0, 4.1))
			return (ft_dprintf(2, MATERIAL_ERROR), 0);
	}
	skip_info(&line);
	if (!(*line))
	{
		mat->tex.type = solid_color;
		mat->get_color = &object_color;
		return (1);
	}
	mat->tex.type = ft_atoi(line);
	if (!in_range((float)mat->tex.type, solid_color, bump_map))
		return (ft_dprintf(2, MATERIAL_ERROR), 0);
	if (mat->tex.type == solid_color)
		mat->get_color = &object_color;
	if (mat->tex.type == checkered)
	{
		mat->get_color = &checkered_color;
		skip_info(&line);
		mat->tex.scale = ft_atof(line);
		skip_info(&line);
		if (!(*line))
			mat->tex.checkered_c = color(0, 0, 0);
		else
			parse_color(&mat->tex.checkered_c, line);
	}
	if (mat->tex.type == image)
	{
		mat->get_color = &image_color;
		//skip_info(&line);
		mat->tex.texture_file = ft_strdup(line);
		mat->tex.texture_file = ft_strtrim(mat->tex.texture_file, " \n\t3");
	}
	//if (mat->tex.type == bump_map)
	//{
	//	mat->get_color = &bump_map_color;
	//	skip_info(&line);
	//	if (!(*line))
	//		mat->tex.checkered_c = color(0, 0, 0);
	//	else
	//		parse_color(mat->tex.checkered_c, line);
	//}
	return (1);
}
