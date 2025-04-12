/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:56:51 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 16:26:52 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

void	print_parsed_elements(t_scene scene);
void	print_plane(t_list *object);
void	print_sphere(t_list *object);
void	print_cylinder(t_list *object);
void	print_quadrilateral(t_list *object);
void	print_point(float p[3]);

#endif
