/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/19 15:53:39 by jcameira         ###   ########.fr       */
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


int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_putendl_fd(NO_ARGS, 2);
	}
	else
	{
		// todo? setter getter
		// init_minirt();
		// setup_mlx();
		// render();
		ft_putendl_fd("parsing", 2);
	}
	return (0);
}
