/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:47:38 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/16 23:32:18 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	toogle_bool(bool *toggle)
{
	if (!toggle)
		return ;
	if (*toggle == true)
		*toggle = false;
	else
		*toggle = true;
}

int	arr_size(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

inline void	print_clean(t_minirt *s)
{
	if (s->render)
		ft_printf("%s", CLEAN);
}
