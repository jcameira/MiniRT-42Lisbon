/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 02:03:52 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_scene(t_scene *scene)
{
	void	*tmp;

	while (scene->lights)
	{
		tmp = scene->lights->next;
		free(scene->lights);
		scene->lights = tmp;
	}
	while (scene->figures)
	{
		tmp = scene->figures->next;
		free(scene->figures);
		scene->figures = tmp;
	}
}

void	skip_info(char **line)
{
	while (**line && (ft_isdigit(**line) || **line == '.' || **line == ','
			|| **line == '-'))
		(*line)++;
	while (**line && (!ft_isdigit(**line) && **line != '-'))
		(*line)++;
}

int	end_minirt(t_minirt *s)
{
	mlx_destroy_image(s->mlx_ptr, s->cam.img.image);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_display(s->mlx_ptr);
	free_scene(&s->scene);
	free(s->mlx_ptr);
	exit(0);
}

int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_ptr, KeyPress, KeyPressMask, &handle_keypress, s);
	mlx_hook(s->win_ptr, ButtonPress, ButtonPressMask, &handle_buttons, s);
	mlx_hook(s->win_ptr, DestroyNotify, StructureNotifyMask, &end_minirt, s);
	// render(s);
	// mlx_loop(s->mlx_ptr);
	return (0);
}

int	setup_mlx(t_scene scene, t_camera cam)
{
	static t_minirt	s;

	s.scene = scene;
	s.cam = cam;
	s.mlx_ptr = mlx_init();
	if (!s.mlx_ptr)
		return (MLX_ERROR);
	s.win_ptr = mlx_new_window(s.mlx_ptr, W, H, WINDOW_NAME);
	if (!s.win_ptr)
	{
		free(s.win_ptr);
		return (MLX_ERROR);
	}
	s.cam.img.image = mlx_new_image(s.mlx_ptr, W, H);
	s.cam.img.data = mlx_get_data_addr(s.cam.img.image, &s.cam.img.bpp,
			&s.cam.img.size_line, &s.cam.img.type);
	setup_hooks(&s);
	miniRT(&s);
	mlx_loop(s.mlx_ptr);
	return (0);
}

int	render(t_minirt *s)
{
	(void)s;
	return (0);
}
int	miniRT(t_minirt *s)
{
	render (s);
	return (0);
}

int	check_scene_elem(char *line)
{
	return ((line[0] == 'A' && (line[1] == 9 || line[1] == 32))
		|| line[0] == 'L' || !ft_strncmp(line, "sp", 2)
		|| !ft_strncmp(line, "pl", 2) || !ft_strncmp(line, "cy", 2));
}

int	parse_point(float (*point)[3], char *line)
{
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!(*line))
		return (ft_fprintf(2, POINT_ERROR), 0);
	(*point)[x] = ft_atof(line);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	if (*line && (*line != ',' || *line + 1 == ','))
		return (ft_fprintf(2, POINT_ERROR), 0);
	line++;
	(*point)[y] = ft_atof(line);
	while (*line && (ft_isdigit(*line) || *line == '.' || *line == '-'))
		line++;
	if (*line && (*line != ',' || *line + 1 == ','))
		return (ft_fprintf(2, POINT_ERROR), 0);
	line++;
	(*point)[z] = ft_atof(line);
	return (1);
}

int	parse_cam(t_camera *cam, char *line)
{
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&cam->o, line))
		return (0);
	skip_info(&line);
	if (!parse_point(&cam->nv, line))
		return (0);
	skip_info(&line);
	cam->fov = ft_atoi(line);
	if (cam->fov <= 0 || cam->fov > 180)
		return (ft_fprintf(2, FOV_ERROR), 0);
	return (1);
}

int	parse_color(char *line)
{
	int	r;
	int	g;
	int	b;

	r = (unsigned char)ft_atoi(line);
	r <<= 16;
	while (*line && ft_isdigit(*line))
		line++;
	if (*line && (*line != ',' || *line + 1 == ','))
		return (ft_fprintf(2, COLOR_ERROR), -1);
	line++;
	g = (unsigned char)ft_atoi(line);
	g <<= 8;
	while (*line && ft_isdigit(*line))
		line++;
	if (*line && (*line != ',' || *line + 1 == ','))
		return (ft_fprintf(2, COLOR_ERROR), -1);
	line++;
	b = (unsigned char)ft_atoi(line);
	return (r | g | b);
}

int	parse_ambience(t_scene *scene, char *line)
{
	static int	already_parsed;

	if (already_parsed)
		return (ft_fprintf(2, MULTIPLE_AMBIENCE), 0);
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!(*line))
		return (ft_fprintf(2, AMBIENCE_ERROR), 0);
	scene->al_br = ft_atof(line);
	skip_info(&line);
	if (!(*line))
		return (ft_fprintf(2, AMBIENCE_ERROR), 0);
	scene->al_c = parse_color(line);
	if (scene->al_c == -1)
		return (0);
	scene->has_al = 1;
	return (1);
}

int	parse_light(t_scene *scene, char *line)
{
	t_light	*new_l;

	new_l = malloc(sizeof(t_light));
	if (!new_l)
		return (ft_fprintf(2, NO_SPACE), 0);
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&new_l->o, line))
		return (free(new_l), 0);
	skip_info(&line);
	new_l->br = ft_atof(line);
	skip_info(&line);
	new_l->c = parse_color(line);
	if (new_l->c == -1)
		return (free(new_l), 0);
	new_l->next = NULL;
	ft_lstadd_back((t_list **)&scene->lights, (t_list *)new_l);
	return (1);
}

int	parse_sphere(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	if (!new_f)
		return (ft_fprintf(2, NO_SPACE), 0);
	new_f->type = SP;
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&new_f->f.sp.c, line))
		return (free(new_f), 0);
	skip_info(&line);
	new_f->f.sp.d = ft_atof(line);
	skip_info(&line);
	new_f->c = parse_color(line);
	if (new_f->c == -1)
		return (free(new_f), 0);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
	return (1);
}

int	parse_plane(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	if (!new_f)
		return (ft_fprintf(2, NO_SPACE), 0);
	new_f->type = PL;
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&new_f->f.pl.p, line))
		return (free(new_f), 0);
	skip_info(&line);
	if (!parse_point(&new_f->f.pl.nv, line))
		return (free(new_f), 0);
	skip_info(&line);
	new_f->c = parse_color(line);
	if (new_f->c == -1)
		return (free(new_f), 0);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
	return (1);
}

int	parse_cylinder(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	if (!new_f)
		return (ft_fprintf(2, NO_SPACE), 0);
	new_f->type = CY;
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&new_f->f.cy.c, line))
		return (free(new_f), 0);
	skip_info(&line);
	if (!parse_point(&new_f->f.cy.nv, line))
		return (free(new_f), 0);
	skip_info(&line);
	new_f->f.cy.d = ft_atof(line);
	skip_info(&line);
	new_f->f.cy.h = ft_atof(line);
	skip_info(&line);
	new_f->c = parse_color(line);
	if (new_f->c == -1)
		return (free(new_f), 0);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
	return (1);
}

int	(*parse_scene_elem(char *line))(t_scene *scene, char *line)
{
	static void	*elem_to_parse[5][2] = {
	{"A", parse_ambience},
	{"L", parse_light},
	{"sp", parse_sphere},
	{"pl", parse_plane},
	{"cy", parse_cylinder},
	};
	char		*tmp;
	int			i;

	tmp = ft_strdup(line);
	if (!tmp)
		return (ft_fprintf(2, NO_SPACE), NULL);
	i = 0;
	while (ft_isalpha(tmp[i]))
		i++;
	tmp[i] = '\0';
	i = -1;
	while (++i < 5)
	{
		if (!ft_strcmp(elem_to_parse[i][0], tmp))
			return (free(tmp), elem_to_parse[i][1]);
	}
	return (free(tmp), NULL);
}

int	parser(t_scene *scene, t_camera *cam, char *file)
{
	char		*line;
	int			file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		return (ft_fprintf(2, FILE_NOT_FOUND, file), 0);
	while (true)
	{
		line = get_next_line(file_fd);
		if (!line)
			return (1);
		if (line[0] == 'C' && (line[1] == 9 || line[1] == 32))
		{
			if (!parse_cam(cam, line))
				return (free(line), 0);
		}
		else if (parse_scene_elem(line))
		{
			if (!(parse_scene_elem(line)(scene, line)))
				return (free(line), 0);
		}
		else if (line[0] != '\n')
			return (ft_fprintf(2, UNKNOWN_ELEMENT, file), free(line), 0);
		free(line);
	}
}

int	check_needed_elements(t_camera cam, t_scene scene, char *file)
{
	if (!cam.fov || !cam.nv || !cam.o)
		return (ft_fprintf(2, NO_CAMERA, file), 0);
	if (!scene.has_al)
		return (ft_fprintf(2, NO_AMBIENCE, file), 0);
	if (!scene.lights)
		return (ft_fprintf(2, NO_LIGHT, file), 0);
	return (1);
}

void	print_parsed_elements(t_camera cam, t_scene scene)
{
	void	*tmp;

	printf("===============CAMERA===============\n");
	printf("Origin -> %f,%f,%f\n", cam.o[x], cam.o[y], cam.o[z]);
	printf("Normalized Vector -> %f,%f,%f\n", cam.nv[x], cam.nv[y], cam.nv[z]);
	printf("Fov -> %d\n", cam.fov);
	printf("===========AMBIENT LIGHT============\n");
	printf("Brithness -> %f\n", scene.al_br);
	printf("Color -> %d,%d,%d\n", scene.al_c >> 16 & 0xFF, scene.al_c >> 8 & 0xFF, scene.al_c & 0xFF);
	printf("===============LIGHTS===============\n");
	tmp = scene.lights;
	while (tmp)
	{
		printf("Origin -> %f,%f,%f\n", ((t_light *)tmp)->o[x], ((t_light *)tmp)->o[y], ((t_light *)tmp)->o[z]);
		printf("Brithness -> %f\n", ((t_light *)tmp)->br);
		printf("Color -> %d,%d,%d\n", ((t_light *)tmp)->c >> 16 & 0xFF, ((t_light *)tmp)->c >> 8 & 0xFF, ((t_light *)tmp)->c & 0xFF);
		printf("\n");
		tmp = ((t_light *)tmp)->next;
	}
	printf("===============FIGURES==============\n");
	tmp = scene.figures;
	while (tmp)
	{
		if (((t_figure *)tmp)->type == SP)
		{
			printf("SPHERE\n");
			printf("Origin -> %f,%f,%f\n", ((t_figure *)tmp)->f.sp.c[x], ((t_figure *)tmp)->f.sp.c[y], ((t_figure *)tmp)->f.sp.c[z]);
			printf("Diameter -> %f\n", ((t_figure *)tmp)->f.sp.d);
		}
		if (((t_figure *)tmp)->type == PL)
		{
			printf("PLANE\n");
			printf("Point -> %f,%f,%f\n", ((t_figure *)tmp)->f.pl.p[x], ((t_figure *)tmp)->f.pl.p[y], ((t_figure *)tmp)->f.pl.p[z]);
			printf("Normalized Vector -> %f,%f,%f\n", ((t_figure *)tmp)->f.pl.nv[x], ((t_figure *)tmp)->f.pl.nv[y], ((t_figure *)tmp)->f.pl.nv[z]);
		}
		if (((t_figure *)tmp)->type == CY)
		{
			printf("CYLINDER\n");
			printf("Origin -> %f,%f,%f\n", ((t_figure *)tmp)->f.cy.c[x], ((t_figure *)tmp)->f.cy.c[y], ((t_figure *)tmp)->f.cy.c[z]);
			printf("Normalized Vector -> %f,%f,%f\n", ((t_figure *)tmp)->f.cy.nv[x], ((t_figure *)tmp)->f.cy.nv[y], ((t_figure *)tmp)->f.cy.nv[z]);
			printf("Diameter -> %f\n", ((t_figure *)tmp)->f.cy.d);
			printf("Height -> %f\n", ((t_figure *)tmp)->f.cy.h);
		}
		printf("Color -> %d,%d,%d\n", ((t_figure *)tmp)->c >> 16 & 0xFF, ((t_figure *)tmp)->c >> 8 & 0xFF, ((t_figure *)tmp)->c & 0xFF);
		printf("\n");
		tmp = ((t_figure *)tmp)->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_camera	cam;

	if (argc != 2)
		return (ft_fprintf(2, NO_ARGS), 1);
	if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))
		|| *(ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) + 3))
		return (ft_fprintf(2, INVALID_RT), 1);
	ft_bzero((void *)&scene, sizeof(scene));
	ft_bzero((void *)&cam, sizeof(cam));
	if (!parser(&scene, &cam, argv[1]) || !check_needed_elements(cam, scene, argv[1]))
		return (free_scene(&scene), 1);
	print_parsed_elements(cam, scene);
	// todo? setter getter
	// init_minirt();
	// setup_mlx();
	setup_mlx(scene, cam);
	return (0);
}
