/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:12:09 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/27 18:48:28 by cjoao-de         ###   ########.fr       */
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
	// t_vertices	*vertices;
	// t_triangle	*triangles;
	float		(*vertices)[3];
	int			(*triangles)[3];
	char		*temp;
	int			obj_fd;

	if (scene->has_obj == 1)
		return ; //(ft_dprintf(2, MULTIPLE_OBJ_FILES), 0);
	line_count = count_lines(fd);
	close(fd);
	// obj_fd = open("scenes/dragon_obj.rt", O_RDONLY); // from terminal
	if (getenv("TERM_PROGRAM") != NULL)	// test for vscode debugging
		obj_fd = open("/home/kajo/42/miniRT/scenes/dragon_obj.rt", O_RDONLY);	// from debugger
	else
		obj_fd = open("scenes/dragon_obj.rt", O_RDONLY); // from terminal
	if (obj_fd < 0)
		return ; //(ft_dprintf(2, FILE_NOT_FOUND, "scenes/dragon_obj.rt"), 0);

	// line_count = 50000;
	printf("F opened with %i lines\n", line_count);	//? end test

	int	vertices_sz = line_count * 0.7;
	int	triangles_sz =	line_count * 0.4;
	ft_dprintf(2, "array created\n");
	// vertices = (t_vertices *)ft_calloc(vertices_sz, sizeof(t_vertices));
	vertices = (float (*)[3])ft_calloc(vertices_sz, sizeof(float[3]));
	// triangles = (t_triangle *)ft_calloc(triangles_sz,  sizeof(t_triangle));
	triangles = ft_calloc(triangles_sz,  sizeof(float[3]));
	ft_dprintf(2, "malloc\n");
	new_f = ft_calloc(1, sizeof(t_figure));
	if (!new_f)
		return ;	//(ft_dprintf(2, NO_SPACE), 0);
	new_f->type = OB;
	int i = 0;
	line = get_next_line(obj_fd);
	//read vertices
	while (*line == 'v')
	{
		temp = line;
		while ((!ft_isdigit(*line) && !ft_issignal(*line)) && *line)
			line++;
		if (!parse_point(&vertices[i], line, 0))
			break ;
		free(temp);
		line = get_next_line(obj_fd);
		i++;
	}
	new_f->f.ob.num_vertices = i;
	ft_printf("\nnumber of points imported: %i\n", new_f->f.ob.num_vertices);
	i = 0;
	//read triangles
	while (*line == 'f')
	{
		temp = line;
		while ((!ft_isdigit(*line) && !ft_issignal(*line)) && *line)
			line++;
		if (!parse_int(&triangles[i], line, 0))
			break ;
		free(temp);
		line = get_next_line(obj_fd);
		if (line == NULL)
			break ;
		i++;
	}
	close(obj_fd);
	new_f->f.ob.num_polys = i;
	ft_printf("number of triangles imported: %i\n", new_f->f.ob.num_polys);
	scene->has_obj = 1;
	// new_f->next = NULL;
	// ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
}
