/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/21 12:36:18 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	end_minirt(t_minirt *s)
{
	mlx_destroy_image(s->mlx_ptr, s->img.image);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_display(s->mlx_ptr);
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

int	setup_mlx(void)
{
	static t_minirt	s;

	s.mlx_ptr = mlx_init();
	if (!s.mlx_ptr)
		return (MLX_ERROR);
	s.win_ptr = mlx_new_window(s.mlx_ptr, W, H, WINDOW_NAME);
	if (!s.win_ptr)
	{
		free(s.win_ptr);
		return (MLX_ERROR);
	}
	s.img.image = mlx_new_image(s.mlx_ptr, W, H);
	s.img.data = mlx_get_data_addr(s.img.image, &s.img.bpp,
			&s.img.size_line, &s.img.type);
	setup_hooks(&s, type);
	miniRT(&s);
	mlx_loop(s.mlx_ptr);
	return (0);
}

int	miniRT(t_minirt *s)
{
	(void)s;
	return (0);
}

int	check_scene_elem(char *line)
{
	return ((line[0] == 'A' && (line[1] == 9 || line[1] == 32))
		|| line[0] == 'L' || !ft_strncmp(line, 'sp', 2)
		|| !ft_strncmp(line, 'pl', 2) || !ft_strncmp(line, 'cy', 2));
}

void	parse_point(t_point *point, char *line)
{
	while (!ft_isdigit(*line))
		line++;
	point->x = ft_atof(line);
	if (*line != ',')
		//error
	line++;
	point->y = ft_atof(line);
	if (*line != ',')
		//error
	line++;
	point->z = ft_atof(line);
	if (*line != ',')
		//error
}

void	parse_cam(t_camera *cam, char *line)
{
	parse_point(cam->o, line);
	parse_point(cam->nv, line);
	while (!ft_isdigit(*line))
		line++;
	cam->fov = ft_atoi(line);
	if (cam->fov < 0 || cam->fov > 180)
		//error
}

int	parse_color(char *line)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(line);
	if (r < 0 || r > 255)
		//error
	r <<= 16;
	if (*line != ',')
		//error
	g = ft_atoi(line);
	if (g < 0 || g > 255)
		//error
	g <<= 8;
	if (*line != ',')
		//error
	b = ft_atoi(line);
	if (b < 0 || b > 255)
		//error
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
	
}

void	parse_ambience(t_scene *scene, char *line)
void	parse_ambience(t_scene *scene, char *line)
void	parse_ambience(t_scene *scene, char *line)

int	(*parse_scene_elem(char *line))(t_scene *scene, char *line)
{
	static void	elem_to_parse[5][2] = {
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
	tmp[i] = NULL;
	i = -1;
	while (++i < 5)
	{
		if (!ft_strcmp(elem_to_parse[i][0], tmp))
			return (elem_to_parse[i][1]);
	}
}

void	parser(t_scene *scene, t_camera *cam, char *file)
{
	char	*line;
	int		file_fd;

	*scene = NULL;
	*cam = NULL;
	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		//error opening file
	while (true)
	{
		line = get_next_line(file_fd);
		if (!line)
			break ;
		if (line[0] == 'C' && (line[1] == 9 || line[1] == 32))
			parse_cam(cam, line);
		else if (check_scene_elem(line))
			parse_scene_elem(scene, line);
		free(line);
	}
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_camera	cam;

	if (argc != 2)
		ft_putendl_fd(NO_ARGS, 2);
	else
	{
		parser(&scene, &cam, argv[1]);
		// todo? setter getter
		// init_minirt();
		// setup_mlx();
		// render();
		ft_putendl_fd("parsing", 2);
	}
	return (0);
}
