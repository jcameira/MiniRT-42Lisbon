/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:41:19 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/31 20:58:46 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*f_name(int idx)
{
	const char	*f_names[] = {
		"SPhere",
		"PLane",
		"CYlinder",
		"COne",
		"QUad",
		"OBject",
		"BBox",
		"Light",
		NULL};
	return ((char *)f_names[idx]);
}
