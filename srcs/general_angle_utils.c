/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_angle_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:33 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 21:13:03 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	to_rad(float degrees)
{
	return (degrees * (M_PI / 180.0f));
}

float	to_deg(float radians)
{
	return (radians * (180.0f / M_PI));
}
