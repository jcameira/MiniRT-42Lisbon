/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:26:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/20 17:43:29 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <float.h>

/*
The memset() function fills the first n bytes of the memory area
pointed to by s with the constant byte c.
The memset() function returns a pointer to the memory area s.
*/

// memset variation to fill float arrays
void	*ft_memset_float(void *s, float f, size_t n)
{
	float	*mem;

	mem = (float *)s;
	while (n-- > 0)
		*mem++ = f;
	return (s);
}
