/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_vector_utlis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:00:21 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 21:14:56 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// linear mapping of a value from one range to another.
// value: The value to be mapped.
// range_: the range_[0] as the lower bound and range_[1] as the upper bound.
float	map(t_rtf value, t_rtf range_orig[2], t_rtf range_dest[2])
{
	return ((value - range_orig[0]) / (range_orig[1] - range_orig[0]) \
				* (range_dest[1] - range_dest[0]) + range_dest[0]);
}

// Normalize: scales a single value to a range [0, 1].
bool	normalize_value(t_rtf *value, t_rtf min, t_rtf max)
{
	if (min == max || *value == 0.0f)
	{
		return (false);
	}
	*value = (*value - min) / (max - min);
	return (true);
}
