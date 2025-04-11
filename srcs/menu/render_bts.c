/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/11 17:30:30 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
rect draw order
current color background > main background > current color
*/
void	draw_color_picker(t_minirt *s)
{
	t_rect	rect;

	rect = (t_rect){MW - 322, 8, 304, 24, GREEN};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){MW - s->assets.bt_clrpick.img.width - 32, 38, \
		s->assets.bt_clrpick.img.width + 4, \
		s->assets.bt_clrpick.img.height + 4, GREEN};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){MW - 320, 10, 300, 20, \
		object_content(s->menu.objects)->mat.c.rgb};
	render_rect(&s->menu.img, rect);
	join_xpm_img(s->menu.img, s->assets.bt_clrpick, \
		MW - s->assets.bt_clrpick.img.width - 30, 40);
}

void	draw_gradients(t_minirt *s)
{
	t_rect	rect;
	int		x_pos;
	int		pad;

	pad = 50;
	rect = (t_rect){38, 224, \
		s->assets.bt_gradient.img.width + 4, \
		s->assets.bt_gradient.img.height + 4, GREEN};
	render_rect(&s->menu.img, rect);
	rect.y += pad;
	render_rect(&s->menu.img, rect);
	rect.y += pad;
	render_rect(&s->menu.img, rect);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40, 226);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40, 276);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40, 326);
	x_pos = (int)(object_content(s->menu.objects)->mat.br \
		* s->assets.bt_gradient.img.width) + 40 + pad;
	rect = (t_rect){x_pos, 278+pad, 2, 30, CYAN};
	render_rect(&s->menu.img, rect);
}

void	draw_brightness_picker(t_minirt *s)
{
	t_rect	rect;
	int		x_pos;
	int		pad;

	pad = 0;

	rect = (t_rect){38+pad, 276, \
		s->assets.bt_gradient.img.width + 4, \
		s->assets.bt_gradient.img.height + 4, GREEN};
	render_rect(&s->menu.img, rect);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40+pad, 228);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40+pad, 278);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40+pad, 328);
	x_pos = (int)(object_content(s->menu.objects)->mat.br \
		* s->assets.bt_gradient.img.width) + 40 + pad;
	rect = (t_rect){x_pos, 278+pad, 2, 30, CYAN};
	render_rect(&s->menu.img, rect);
}

// static void	draw_fuzz_picker(t_minirt *s)
// {
// 	t_rect	rect;
// 	int		x_pos;

// 	x_pos = (int)(object_content(s->menu.objects)->mat.br \
// 		* s->assets.bt_gradient.img.width) + 40;
// 	rect = (t_rect){x_pos, 278, 2, 30, CYAN};
// 	render_rect(&s->menu.img, rect);
// }

/*
static void	draw_ri_picker(t_minirt *s)
{
	t_rect	rect;
	int		x_pos;
	int		pad;

	pad = 0;

	rect = (t_rect){38+pad, 276, \
		s->assets.bt_gradient.img.width + 4, \
		s->assets.bt_gradient.img.height + 4, GREEN};
		render_rect(&s->menu.img, rect);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40+pad, 228);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40+pad, 278);
	join_xpm_img(s->menu.img, s->assets.bt_gradient, 40+pad, 328);
	x_pos = (int)(object_content(s->menu.objects)->mat.br \
		* s->assets.bt_gradient.img.width) + 40 + pad;
	rect = (t_rect){x_pos, 278+pad, 2, 30, CYAN};
	render_rect(&s->menu.img, rect);
}
*/

void	draw_quality_picker(t_minirt *s)
{
	t_rect		rect;
	int			width;
	int			height;
	t_circle	c;

	width = 70;
	height = 30;
	rect = (t_rect){40, 374, width, height, BLUE};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){40 + width * 1, 374, width, height, GREEN};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){40 + width * 2, 374, width, height, MAGENTA};
	render_rect(&s->menu.img, rect);
	rect = (t_rect){40 + width * 3, 374, width, height, RED};
	render_rect(&s->menu.img, rect);
	c =	(t_circle){40 + width / 2 + (s->scene.quality_idx * width), \
	374 + height / 2, 8, BLACK};
	draw_circle_fill(s->menu.img, c);
}
