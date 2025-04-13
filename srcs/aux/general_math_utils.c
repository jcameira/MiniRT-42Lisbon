/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_math_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:01:47 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/13 22:43:23 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	ft_fmin(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

//! not used
bool	is_maxf(float this, float that)
{
	if (this > that)
		return (true);
	return (false);
}

// mix: returns the linear interpolation between two values.
//! not used
float	mixf(float a, float b, float t)
{
	return (a + t * (b - a));
}

// mid: returns the median between two values.
//! not used
float	medf(float a, float b)
{
	return ((a + b) / 2);
}
