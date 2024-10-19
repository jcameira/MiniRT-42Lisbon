/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 01:32:31 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/19 01:01:00 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
// #include <stdio.h>
// #include <string.h>

/*
void	*ft_memset(void *s, int c, size_t n)
{
	char	*mem;

	mem = s;
	while (n-- > 0)
		*mem++ = c;
	return (0);
}
*/

/*
The bzero() function erases the data in the n bytes
of the memory starting at the location pointed to by s,
by writing zeros (bytes containing '\0') to that area.
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*
void	test_bzero(void)
{
	char	str[10];

	ft_bzero(str, 10);
	if (memcmp(str, "\0\0\0\0\0\0\0\0\0\0", 10) != 0)
		printf("ft_bzero test failed\n");
	else
		printf("ft_bzero test passed\n");
}

int	main(void)
{
	test_bzero();
	test_memset();
	return (0);
}
*/
