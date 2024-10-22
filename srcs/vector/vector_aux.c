/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:34:13 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/22 16:51:42 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	to_rad(float degrees) {
	return degrees * (M_PI / 180.0f);
}
float	to_deg(float radians) {
	return radians * (180.0f / M_PI);
}

// linear mapping of a value from one range to another.
// value: The value to be mapped.
// range_: the range_[0] as the lower bound and range_[1] as the upper bound.
float	map(rtf value, rtf range_orig[2], rtf range_dest[2])
{
	return ((value - range_orig[0]) / (range_orig[1]- range_orig[0]) \
				* (range_dest[1] - range_dest[0]) + range_dest[0]);
}
// Normalize: scales a single value to a range [0, 1].
bool normalize_value(rtf *value, rtf min, rtf max)
{
	if (min == max || *value == 0.0f)
	{
		return false;
	}
	*value = (*value - min) / (max - min);
	return true;
}

bool	is_maxf(float this, float that)
{
	if (this > that)
		return (true);
	return (false);
}
// mix: returns the linear interpolation between two values.
float	mixf(float a, float b, float t)
{
	return a + t * (b - a);
}

// mid: returns the median between two values.
float	medf(float a, float b)
{
	return ((a + b) / 2);
}
// Clamp: restricts a value to lie within a specified range.
float clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}
