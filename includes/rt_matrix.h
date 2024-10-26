/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_matrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:15:15 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/26 20:17:29 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATRIX_H
# define RT_MATRIX_H

void	mul_vec_by_mat(float **vec, float **mat);
void	orthographic(float **vec);
void	apply_rotation(float **vec, int angle, t_xyz axis);

#endif