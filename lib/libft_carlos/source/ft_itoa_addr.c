/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_addr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:55:26 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/05 12:38:45 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// #include <unistd.h>
// #include <limits.h>

/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
Returns
The string representing the integer.
NULL if the allocation fails.
*/

// static char	*itoa_loop(int len, long divisor, long lnb, int signal)
static char	*itoa_loop(long divisor, long lnb, int signal, char	*itoa_str)
{
	int		i;

	i = 0;
	if (signal == 1)
	{
		itoa_str[0] = '-';
		i = 1;
	}
	while (divisor)
	{
		itoa_str[i] = lnb / divisor + '0';
		lnb = lnb % divisor;
		divisor = divisor / 10;
		i++;
	}
	itoa_str[i] = '\0';
	return (itoa_str);
}

char	*ft_itoa_addr(int n, char *itoa_str)
{
	long	divisor;
	long	lnb;
	int		itoa_len;
	int		i;

	itoa_len = 2;
	lnb = (long)n;
	divisor = 1;
	i = 0;
	if (n < INT_MIN || n > INT_MAX)
		return (NULL);
	if (lnb < 0 && itoa_len++)
	{
		i = 1;
		lnb = -lnb;
	}
	while (divisor * 10 <= lnb && itoa_len++)
		divisor = divisor * 10;
	itoa_str = itoa_loop(divisor, lnb, i, itoa_str);
	return (itoa_str);
}
