/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:12:09 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/24 21:01:52 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// General parsing function for a 3 axis point or 3D normalized vector that
// should be written in the given file exectly as such -> x,y,z
// For a 3D normalized vector the values of x, y and z should be in the
// interval of [-1, 1]
int	parse_int(int (*list)[3], char *line, int vector)
{
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!(*line))
		return (ft_dprintf(2, POINT_ERROR), 0);
	(*list)[x] = ft_atoi(line);
	if (vector && !in_range((*list)[x], NV_AXIS_MIN, NV_AXIS_MAX))
		return (ft_dprintf(2, POINT_ERROR), 0);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	line++;
	(*list)[y] = ft_atoi(line);
	if (vector && !in_range((*list)[y], NV_AXIS_MIN, NV_AXIS_MAX))
		return (ft_dprintf(2, POINT_ERROR), 0);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	line++;
	(*list)[z] = ft_atoi(line);
	if (vector && !in_range((*list)[z], NV_AXIS_MIN, NV_AXIS_MAX))
		return (ft_dprintf(2, POINT_ERROR), 0);
	return (1);
}

/*
open a OBJ definition file, and imports each line
into vertexs and shapes
31v			56f			1.8
1190v		1608f		1.351
175636v		349887f		f/v	1.9921
*/
void	parse_object(t_scene *scene, int fd)
{
	int			line_count;
	t_figure	*new_f;
	char		*line;
	t_vertices	*vertices;
	t_triangle	*triangles;

	if (scene->has_obj == 1)
		return ; //(ft_dprintf(2, MULTIPLE_OBJ_FILES), 0);
	// line_count = count_lines(fd);
	line_count = 87;
	printf("F opened with %i lines\n", line_count);	//? end test

	int	vertices_sz = line_count * 0.7;
	int	triangles_sz =	line_count * 0.4;
	vertices = (t_vertices *)ft_calloc(line_count, vertices_sz * sizeof(t_vertices));
	triangles = (t_triangle *)ft_calloc(line_count, triangles_sz * sizeof(t_triangle));
	new_f = ft_calloc(1, sizeof(t_figure));
	if (!new_f)
		return ;	//(ft_dprintf(2, NO_SPACE), 0);
	new_f->type = OB;
	int i = 0;
	line = get_next_line(fd);
	//read vertices
	while (*line == 'v')
	{
		// skip_info(&line);
		while ((!ft_isdigit(*line) && !ft_issignal(*line)) && *line)
			line++;
		if (!parse_point(&vertices[i].pos, line, 0))
			break ;
		line = get_next_line(fd);
		i++;
	}
	new_f->f.ob.num_vertices = i;
	i = 0;
	//read triangles
	while (*line == 'f')
	{
		while ((!ft_isdigit(*line) && !ft_issignal(*line)) && *line)
			line++;
		if (!parse_int(&triangles[i].vertex_list, line, 0))
		break ;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		i++;
	}
	close(fd);
	new_f->f.ob.num_polys = i;
	scene->has_obj = 1;
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
}
