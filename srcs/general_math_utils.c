/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_math_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:01:47 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/09 13:25:52 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	is_maxf(float this, float that)
{
	if (this > that)
		return (true);
	return (false);
}

// mix: returns the linear interpolation between two values.
float	mixf(float a, float b, float t)
{
	return (a + t * (b - a));
}

// mid: returns the median between two values.
float	medf(float a, float b)
{
	return ((a + b) / 2);
}

// Clamp: restricts a value to lie within a specified range.
int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

// Clamp: restricts a value to lie within a specified range.
float	clampf(float value, float min, float max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}
