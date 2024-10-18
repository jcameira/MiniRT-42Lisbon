/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_addr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:55:26 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/05 17:18:46 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// converts a float to ascii, uses itoa for integer and then decimal part.
// If the destination buffer, limited by its size, isn't large enough
// to hold the copy, the resulting string is truncated.
// NOT WORKING, MAYBE LATER
// char	*ft_ftoa_addr(float nbr, int precision, char *ftoa_str)
// {
// 	int			integer;
// 	int			decimal;
// 	char		*integer_c;
// 	char		*decimal_c;
// 	int			len;

// 	// integer_c = NULL;
// 	// decimal_c = NULL;
// 	integer = (int)nbr;
// 	decimal = (int)((nbr - integer) * precision);
// 	integer_c = ft_itoa(ft_abs(integer));
// 	decimal_c = ft_itoa(ft_abs(decimal));
// 	// ft_memset(ftoa_str, 0, 6);
// 	// ft_itoa_addr(ft_abs(integer), integer_c);
// 	// ft_itoa_addr(ft_abs(decimal), decimal_c);
// 	len = ft_strlen(integer_c) + ft_strlen(decimal_c) + 1;
// 	if (nbr < 0)
// 		ft_strlcat(ftoa_str, "-", len + 1);
// 	ft_strlcat(ftoa_str++, integer_c, len);
// 	ft_strlcat(ftoa_str++, ".", 1);
// 	ft_strlcat(ftoa_str++, decimal_c, len);
// 	free (integer_c);
// 	free (decimal_c);
// 	return (ftoa_str);
// }
