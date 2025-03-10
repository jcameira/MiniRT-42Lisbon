/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:23:14 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/10 18:33:14 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_camera	cam;

	if (argc != 2)
		return (ft_dprintf(2, NO_ARGS), 1);
	if (!ft_strnstr(argv[y], ".rt", ft_strlen(argv[y]))
		|| *(ft_strnstr(argv[y], ".rt", ft_strlen(argv[y])) + 3))
		return (ft_dprintf(2, INVALID_RT), 1);
	ft_bzero((void *)&scene, sizeof(scene));
	if (!parser(&scene, &cam, argv[y])
		|| !check_needed_elements(cam, scene, argv[y]))
		return (free_scene(&scene), 1);
	int i = -1;
	while (++i < scene.obj_nbr)
		printf("Object type -> %d\n", ((t_figure *)scene.objects[i])->type);
	print_parsed_elements(cam, scene);
	setup_minirt(scene, cam);
	return (0);
}