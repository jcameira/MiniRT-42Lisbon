/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/20 17:07:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minirt.h"
#include "../lib/libft/include/libft.h"

int	main(void)
{
	char	*pos;
	char	*zero;
	char	*neg;
	char	*negneg;

	pos = "1.100a2";
	zero = "0.00a00";
	neg = "-0.45a6";
	negneg = "-5.0a48";
	printf("%f\n", ft_atof(pos));
	printf("%f\n", ft_atof(zero));
	printf("%f\n", ft_atof(neg));
	printf("%f\n", ft_atof(negneg));
	return (0);
}
