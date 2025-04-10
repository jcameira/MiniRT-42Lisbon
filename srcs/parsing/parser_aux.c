/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:12:09 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/10 18:33:20 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	skip_info(char **line)
{
	while (**line && (ft_isdigit(**line) || **line == '.' || **line == ','
			|| ft_issignal(**line)))
		(*line)++;
	while (**line && (!ft_isdigit(**line) && !ft_issignal(**line)))
		(*line)++;
}
