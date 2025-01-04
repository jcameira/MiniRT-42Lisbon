/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:47:38 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/04 04:31:48 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	toogle_bool(bool *toggle)
{
	if (!toggle)
		return ;
	if (*toggle == true)
		*toggle = false;
	else if (*toggle == false)
		*toggle = true;
}

// returns the number of lines in a given fd
int	count_lines(int fd)
{
	int		count;
	char	buffer[512];
	ssize_t	bytes_read;
	int		i;

	if (fd < 0)
		return (-1);
	count = 0;
	while (true)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read <= 0)
			break ;
		i = -1;
		while (++i < bytes_read)
		{
			if (buffer[i] == '\n')
				count++;
		}
	}
	return (count);
}


