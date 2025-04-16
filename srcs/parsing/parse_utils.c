/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:13:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 13:21:51 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// General parsing function for a 3 axis point or 3D normalized vector that
// should be written in the given file exectly as such -> x,y,z
// For a 3D normalized vector the values of x, y and z should be in the
// interval of [-1, 1]
int	parse_point(float (*point)[3], char *line, int vector)
{
	char	**point_info;

	if (line[0] == ',' || line[ft_strlen(line) - 1] == ',')
		return (ft_dprintf(2, POINT_ERROR), 0);
	point_info = ft_split(line, ',');
	if (!point_info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(point_info) != 3)
		return (ft_dprintf(2, POINT_ERROR), free_arr((void **)point_info), 0);
	if (!check_if_float(point_info[0]) || !check_if_float(point_info[1])
		|| !check_if_float(point_info[2]))
		return (ft_dprintf(2, POINT_ERROR), free_arr((void **)point_info), 0);
	(*point)[x] = ft_atof(point_info[0]);
	(*point)[y] = ft_atof(point_info[1]);
	(*point)[z] = ft_atof(point_info[2]);
	if (vector && (!in_range((*point)[x], NV_AXIS_MIN, NV_AXIS_MAX)
		|| !in_range((*point)[y], NV_AXIS_MIN, NV_AXIS_MAX)
		|| !in_range((*point)[z], NV_AXIS_MIN, NV_AXIS_MAX)))
		return (ft_dprintf(2, POINT_ERROR), 0);
	return (1);
}

// General parsing function for an rgb color that should be written in
// the given file exectly as such -> r,g,b
// Each of the values of r, g and b should be in the interval of [0, 255]
int	parse_color(t_pixel *c, char *line)
{
	char	**color_info;

	if (line[0] == ',' || line[ft_strlen(line) - 1] == ',')
		return (ft_dprintf(2, COLOR_ERROR), 0);
	color_info = ft_split(line, ',');
	if (!color_info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(color_info) != 3)
		return (ft_dprintf(2, COLOR_ERROR), free_arr((void **)color_info), 0);
	if (!check_if_int(color_info[0]) || !check_if_int(color_info[1])
		|| !check_if_int(color_info[2]))
		return (ft_dprintf(2, COLOR_ERROR), free_arr((void **)color_info), 0);
	c->r = ft_atoi(color_info[0]);
	c->g = ft_atoi(color_info[1]);
	c->b = ft_atoi(color_info[2]);
	if (!in_range((float)c->r, (float)RGB_MIN, (float)RGB_MAX)
		|| !in_range((float)c->g, (float)RGB_MIN, (float)RGB_MAX)
		|| !in_range((float)c->b, (float)RGB_MIN, (float)RGB_MAX))
		return (ft_dprintf(2, COLOR_ERROR), free_arr((void **)color_info), 0);
	c->rgb = c->r << 16 | c->g << 8 | c->b;
	return (free_arr((void **)color_info), 1);
}

void	set_scatter(t_material *mat)
{
	if (mat->type == lambertian)
		mat->scatter = &lambertian_scatter;
	else if (mat->type == specular)
		mat->scatter = &specular_scatter;
	else if (mat->type == dialetric)
		mat->scatter = &dialetric_scatter;
	else if (mat->type == emission)
		mat->scatter = &lambertian_scatter;
}

void	set_texture_get_color(t_material *mat)
{
	if (mat->tex.type == solid_color)
		mat->get_color = &object_color;
	else if (mat->tex.type == checkered)
		mat->get_color = &checkered_color;
	else if (mat->tex.type == image)
		mat->get_color = &image_color;
	else if (mat->tex.type == bump_map)
		mat->get_color = &bump_color;
}

int	parse_material(t_material *mat, char **info)
{
	if (!check_if_int(info[0]) || !check_if_float(info[1])
		|| !check_if_float(info[2]) || !check_if_int(info[3])
		|| !check_if_float(info[4])
		|| !parse_color(&mat->tex.checkered_c, info[5]))
		return (ft_dprintf(2, SPHERE_USAGE), 0);
	mat->type = ft_atoi(info[0]);
	if (!in_range((float)mat->type, lambertian, emission))
		return (ft_dprintf(2, SPHERE_USAGE), 0);
	set_scatter(mat);
	mat->fuzz = ft_atof(info[1]);
	mat->ri = ft_atof(info[2]);
	mat->tex.type = ft_atoi(info[3]);
	if (!in_range((float)mat->type, solid_color, bump_map))
		return (ft_dprintf(2, SPHERE_USAGE), 0);
	set_texture_get_color(mat);
	mat->tex.scale = ft_atof(info[4]);
	mat->tex.img_texture_file = ft_strdup(info[6]);
	if (!mat->tex.img_texture_file)
		return (ft_dprintf(2, NO_SPACE), 0);
	mat->tex.img_texture.image = NULL;
	mat->tex.bump_texture_file = ft_strdup(info[7]);
	if (!mat->tex.bump_texture_file)
		return (ft_dprintf(2, NO_SPACE), 0);
	mat->tex.bump_texture.image = NULL;
	return (1);
}
