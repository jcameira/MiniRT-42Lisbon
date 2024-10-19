/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:40:44 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/19 01:20:01 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
//#include <stdio.h>
//#include <string.h>

/* from man
The strchr() function returns a pointer
to the first occurrence of the character c in the string s.
*/

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

/*
int	main(void)
{
	const char *str = "Hello, world!";
	char searchChar = '0';
	char *result = ft_strchr(str, searchChar);
	char *stdResult = strchr(str, searchChar);
	int len = ft_strchr(str, '\0') - str;

	printf("alternative StrLen: %i \n", len);
	if (result != NULL) {
		printf("Using ft_strchr: Found character ");
		printf("'%c' at position %ld\n", searchChar, result - str);
	} else {
	} else {
		printf("Using ft_strchr: Character ");
		printf("'%c' not found\n", searchChar);
	}

	if (stdResult != NULL) {
		printf("Using strchr: Found character ");
		printf("'%c' at position %ld\n", searchChar, stdResult - str);
	} else {
		printf("Using strchr:    Character ");
		printf("'%c' not found\n");
	}
	return 0;
}
*/
