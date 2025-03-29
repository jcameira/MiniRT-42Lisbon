/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/11 21:00:01 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	mouse_menu(int button, int x, int y, void *param)
{
	t_minirt *p;
	static int count;

	p = (t_minirt *)param;
	if (p->menu.click_spam == false)
	{
		if ((x >= 20 && x <= 40) && (y >= 440 && y <= 460))
		{
			count++;
			printf("%i\n", count);
			radio_one(p);
		}
		if ((x >= 20 && x <= 40) && (y >= 490 && y <= 510))
		{
			count++;
			printf("%i\n", count);
			radio_two(p);
		}
		if ((x >= 20 && x <= 40) && (y >= 540 && y <= 560))
		{
			count++;
			printf("%i\n", count);
			radio_three(p);
		}
		if ((x >= 20 && x <= 40) && (y >= 590 && y <= 610))
		{
			count++;
			printf("%i\n", count);
			radio_four(p);
		}
		if ((x >= (MW - 134) / 2 && x <= (MW + 134) / 2) && (y >= 360 && y <= 414))
		{
			printf("%s\n", "clicked render");
			render_bt(p);
		}
		// if ((x >= 20 && x <= 320) && (y >= 20 && y <= 360))
		if ((x >= MW - p->assets.bt_clrpick.width - 30 && x <= MW - 30) \
			&& (y >= 40 && y <= p->assets.bt_clrpick.height + 40))
		// p->assets.bt_clrpick.height
		// p->assets.bt_clrpick.width
			color_picker(p, x, y);
		printf("Mouse in %s, button %d at %dx%d.\n", MENU_NAME, button, x, y);
		printf("color picked %d\n",  object_content(p->menu.objects)->mat.c.rgb);

		// printf("color picked %d\n", p->menu.color_picker.rgb);
	}
	return (render_menu(p), 1);
}
