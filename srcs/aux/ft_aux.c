/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:47:38 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/20 19:52:53 by cjoao-de         ###   ########.fr       */
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

time_t	get_time(void)
{
	struct timeval	timestamp;

	if (gettimeofday(&timestamp, NULL) != 0)
		printf("error getting timestamp");
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

// time in ms
void	print_time(time_t time)
{
	int carry;
	int res;

	ft_printf("%s", "Render took: ");
	carry = (int)time;
	res = carry / 3600000;
	ft_printf("%ih ", res);
	carry -= (res * 3600000);
	res = carry / 60000;
	ft_printf("%im ", res);
	carry -= (res * 60000);
	res = carry / 1000;
	ft_printf("%is ", res);
	carry -= (res * 1000);
	ft_printf("%ims\n", carry);
}
