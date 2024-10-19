/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:20:48 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/19 01:20:30 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
// #include <stdio.h>
// #include <stdlib.h>
/*
static int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}
*/
char	*ft_strdup(const char *src)
{
	size_t	size;
	char	*dup;
	int		i;

	i = 0;
	size = ft_strlen(src) + 1;
	dup = (char *)malloc(sizeof(char) * size);
	if (!dup)
		return (NULL);
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
int	main(void)
{
	char	*old;
	char	*new;

	old = "eu sou uma string";
	new = ft_strdup(old);
	return (0);
} */
