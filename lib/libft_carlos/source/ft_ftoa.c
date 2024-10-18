/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:55:26 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/04/07 20:30:13 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// aux function to ft_ftoa, concatenates final string
char	*ft_strjoin_ftoa(char *int_c, char *dec_c, int zeroes, int signal)
{
	char		*res;
	char		*temp;

	if (signal < 0)
	{
		res = ft_strjoin("-", int_c);
		temp = res;
		res = ft_strjoin(res, ".");
		free(temp);
	}
	else
		res = ft_strjoin(int_c, ".");
	while (--zeroes > 0)
	{
		temp = res;
		res = ft_strjoin(res, "0");
		free(temp);
	}
	temp = res;
	res = ft_strjoin(res, dec_c);
	free(temp);
	return (res);
}

// converts a float to ascii, uses itoa for integer and then decimal part.
// returns a malloc'ed string
char	*ft_ftoa(float nbr, int precision)
{
	char		*res;
	char		*integer_c;
	char		*decimal_c;
	int			zeroes;
	float		decimal;

	zeroes = 0;
	integer_c = ft_itoa(ft_abs((int)nbr));
	decimal_c = ft_itoa(ft_fabsf((int)((nbr - (int)nbr) * precision)));
	decimal = ft_fabsf((int)nbr - nbr);
	while (decimal < 1 && decimal != 0 && ++zeroes)
		decimal *= 10;
	if (nbr < 0)
		res = ft_strjoin_ftoa(integer_c, decimal_c, zeroes, -1);
	else
		res = ft_strjoin_ftoa(integer_c, decimal_c, zeroes, 1);
	free(integer_c);
	free(decimal_c);
	return (res);
}
