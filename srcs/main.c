/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/26 23:12:10 by jcameira         ###   ########.fr       */
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

int render(t_minirt *s)
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

void	parse_point(float (*point)[3], char *line)
{
	while (!ft_isdigit(*line))
		line++;
	(*point)[x] = ft_atof(line);
	//if (*line != ',')
	//	error
	line++;
	(*point)[y] = ft_atof(line);
	//if (*line != ',')
	//	error
	line++;
	(*point)[z] = ft_atof(line);
	//if (*line != ',')
	//	error
}

void	parse_cam(t_camera *cam, char *line)
{
	parse_point(&cam->o, line);
	parse_point(&cam->nv, line);
	while (!ft_isdigit(*line))
		line++;
	cam->fov = ft_atoi(line);
	//if (cam->fov < 0 || cam->fov > 180)
	//	error
}

int	parse_color(char *line)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(line);
	//if (r < 0 || r > 255)
	//	error
	r <<= 16;
	// if (*line != ',')
	// 	error
	g = ft_atoi(line);
	//if (g < 0 || g > 255)
	//	error
	g <<= 8;
	// if (*line != ',')
	// 	error
	b = ft_atoi(line);
	//if (b < 0 || b > 255)
	//	error
	return(r | g | b);
}

void	parse_ambience(t_scene *scene, char *line)
{
	while (!ft_isdigit(*line))
		line++;
	scene->al_br = ft_atof(line);
	while (!ft_isdigit(*line))
		line++;
	scene->al_br = parse_color(line);
}

void	parse_light(t_scene *scene, char *line)
{
	t_light	*new_l;

	new_l = malloc(sizeof(t_light));
	//if (!new_l)
	//	error
	while (!ft_isdigit(*line))
		line++;
	parse_point(&new_l->o, line);
	while (!ft_isdigit(*line))
		line++;
	new_l->br = ft_atof(line);
	while (!ft_isdigit(*line))
		line++;
	new_l->c = parse_color(line);
	new_l->next = NULL;
	ft_lstadd_back((t_list **)&scene->lights, (t_list *)new_l);
}

void	parse_sphere(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	//if (!new_f)
	//	error
	new_f->type = SP;
	while (!ft_isdigit(*line))
		line++;
	parse_point(&new_f->f.sp.c, line);
	while (!ft_isdigit(*line))
		line++;
	new_f->f.sp.d = ft_atof(line);
	while (!ft_isdigit(*line))
		line++;
	new_f->c = parse_color(line);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
}

void	parse_plane(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	//if (!new_f)
	//	error
	new_f->type = PL;
	while (!ft_isdigit(*line))
		line++;
	parse_point(&new_f->f.pl.p, line);
	while (!ft_isdigit(*line))
		line++;
	parse_point(&new_f->f.pl.nv, line);
	while (!ft_isdigit(*line))
		line++;
	new_f->c = parse_color(line);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
}

void	parse_cylinder(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	//if (!new_f)
	//	error
	new_f->type = CY;
	while (!ft_isdigit(*line))
		line++;
	parse_point(&new_f->f.cy.c, line);
	while (!ft_isdigit(*line))
		line++;
	parse_point(&new_f->f.cy.nv, line);
	while (!ft_isdigit(*line))
		line++;
	new_f->f.cy.d = ft_atof(line);
	while (!ft_isdigit(*line))
		line++;
	new_f->f.cy.h = ft_atof(line);
	while (!ft_isdigit(*line))
		line++;
	new_f->c = parse_color(line);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
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

	tmp = line;
	i = 0;
	while (ft_isalpha(tmp[i]))
		i++;
	tmp[i] = '\0';
	i = -1;
	while (++i < 5)
	{
		if (!ft_strcmp(elem_to_parse[i][0], tmp))
			return (elem_to_parse[i][1]);
	}
	return (NULL);
}

void	parser(t_scene *scene, t_camera *cam, char *file)
{
	char	*line;
	int		file_fd;
	t_figure	*tmp;

	scene->figures = NULL;
	scene->lights = NULL;
	file_fd = open(file, O_RDONLY);
	//if (file_fd < 0)
	//	error opening file
	while (true)
	{
		line = get_next_line(file_fd);
		if (!line)
			break ;
		if (line[0] == 'C' && (line[1] == 9 || line[1] == 32))
			parse_cam(cam, line);
		else if (check_scene_elem(line) && parse_scene_elem(line))
			parse_scene_elem(line)(scene, line);
		free(line);
	}
	tmp = scene->figures;
	while (scene->figures)
		scene->figures = scene->figures->next;
	scene->figures = tmp;
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_camera	cam;

	if (argc != 2)
		ft_putendl_fd(NO_ARGS, 2);
	else
	{
		// todo? error messages for bad parsing
		parser(&scene, &cam, argv[1]);
		// todo? setter getter
		// init_minirt();
		// setup_mlx();
		setup_mlx(scene, cam);
		// render();
		ft_putendl_fd("parsing", 2);

	}
	return (0);
}
