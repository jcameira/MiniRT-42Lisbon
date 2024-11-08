/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/11/08 13:55:51 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <debug.h>

static t_minirt	s;
object test_object;   // the test object

int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_ptr, KeyPress, KeyPressMask, &handle_keypress, s);
	// mlx_hook(s->win_ptr, ButtonPress, ButtonPressMask, &handle_buttons, s);
	mlx_hook(s->win_ptr, DestroyNotify, StructureNotifyMask, &end_minirt, s);
	return (0);
}


int	setup_mlx(t_scene scene, t_camera cam, char *argv1)
{
	// static t_minirt	s;

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
	minirt(&s, argv1);
	mlx_loop(s.mlx_ptr);
	return (0);
}

int	render(t_minirt *s, char *argv1)
{
	(void)s;
	int index,   // looping variable
	done=0;  // exit flag
	// object test_object;   // the test object
	char buffer[80]; // used to print strings
	if (!PLG_Load_Object(&test_object,argv1,1))
	{
	printf("\nCouldn't find file %s\n",argv1);
	// position the object
	test_object.world_pos.x = 0;
	test_object.world_pos.y = 0;
	test_object.world_pos.z = 300;
	viewing_distance = 250;
	return (0);
	}
	while (done < 10)
	{
		Rotate_Object((object_ptr)&test_object,2,4,6);
	// convert the local coordinates into camera coordinates for projection
	// note the viewer is at (0,0,0) with angles 0,0,0 so the transformaton
	// is simply to add the world position to each local vertex
		for (index=0; index<test_object.num_vertices; index++)
		{
			test_object.vertices_camera[index].x =
				test_object.vertices_local[index].x+test_object.world_pos.x;
			test_object.vertices_camera[index].y =
				test_object.vertices_local[index].y+test_object.world_pos.y;
			test_object.vertices_camera[index].z =
				test_object.vertices_local[index].z+test_object.world_pos.z;
		} // end for index

		// draw the object
		Draw_Object_Wire((object_ptr)&test_object, s);
		// print out position of object
		sprintf(buffer,"Object is at (%d,%d,%d)   ",(int)test_object.world_pos.x,
													(int)test_object.world_pos.y,
													(int)test_object.world_pos.z);

		printf("%s\n", buffer);
		mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->cam.img.data, 0, 0);
		done++;
	}

	return (0);
}

int	minirt(t_minirt *s, char *argv1)
{
	render (s, argv1);
	return (0);
}

int	not_main(int argc, char **argv)
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
	if (!parser(&scene, &cam, argv[1])
		|| !check_needed_elements(cam, scene, argv[1]))
		return (free_scene(&scene), 1);
	print_parsed_elements(cam, scene);
	// setup_mlx(scene, cam);
	return (0);
}
