/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 16:26:33 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTOR_H
# define RT_VECTOR_H

typedef float	t_rtf;
//	typedef double	rtd;

//	vector
//	standard
void	vec3_copyf(t_rtf result[3], const t_rtf vector[3]);
// void	vec4_copyi(int result[4], const int vector[4]);
void	vec2_copyf(t_rtf result[2], const t_rtf vector[2]);
void	vec3_addf(t_rtf result[3], const t_rtf vector0[3],
			const t_rtf vector1[3]);
void	vec2_addf(t_rtf result[2], const t_rtf vector0[2],
			const t_rtf vector1[2]);
void	vec3_subf(t_rtf result[3], const t_rtf vector0[3],
			const t_rtf vector1[3]);
void	vec2_subf(t_rtf result[2], const t_rtf vector0[2],
			const t_rtf vector1[2]);
float	vec3_dotf(const t_rtf vector0[3], const t_rtf vector1[3]);
float	vec2_dotf(const t_rtf vector0[2], const t_rtf vector1[2]);
void	vec3_scalef(t_rtf result[3], const t_rtf vector[3], const t_rtf scalar);
void	vec2_scalef(t_rtf result[2], const t_rtf vector[2], const t_rtf scalar);
float	vec3_lenf(const t_rtf vector[3]);
float	vec2_lenf(const t_rtf vector[2]);
bool	vec3_normalizef(t_rtf vector[3]);
bool	vec2_normalizef(t_rtf vector[2]);
bool	vec3_near_zerof(const float vector[3]);

//	advanced
void	vec3_crossf(t_rtf result[3], const t_rtf vector0[3],
			const t_rtf vector1[3]);
float	vec3_angle(const float vector0[3], const float vector1[3]);
void	vec3_project(t_rtf result[3], const t_rtf vector0[3],
			const t_rtf vector1[3]);

//	aux
float	to_rad(float degrees);
float	to_deg(float radians);
float	map(t_rtf value, t_rtf range_orig[2], t_rtf range_dest[2]);
bool	normalize_value(t_rtf *value, t_rtf min, t_rtf max);
bool	is_maxf(float this, float that);
float	medf(float a, float b);
float	mixf(float a, float b, float t);
int		clamp(int value, int min, int max);
float	clampf(float value, float min, float max);

#endif
