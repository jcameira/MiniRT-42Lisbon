/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:59:41 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/01 17:17:24 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pixel	object_color(t_list *obj, t_hitrecord *hit)
{
    (void)hit;
	return (object_content(obj)->mat.c);
}