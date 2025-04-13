/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_angle_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:33 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/10 18:51:04 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

inline float	to_rad(float degrees)
{
	return (degrees * (M_PI / 180.0f));
}

inline float	to_deg(float radians)
{
	return (radians * (180.0f / M_PI));
}
