/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/31 17:06:08 by cjoao-de         ###   ########.fr       */
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
/*
GLUSvoid GLUSAPIENTRY glusVector2GetPoint3f(GLUSfloat result[3], const GLUSfloat vector[2]);
GLUSboolean GLUSAPIENTRY glusVector3GramSchmidtOrthof(GLUSfloat result[3], const GLUSfloat u[3], const GLUSfloat v[3]);
GLUSboolean GLUSAPIENTRY glusVector2GramSchmidtOrthof(GLUSfloat result[2], const GLUSfloat u[2], const GLUSfloat v[2]);
GLUSvoid GLUSAPIENTRY glusVector3Reflectf(GLUSfloat result[3], const GLUSfloat incident[3], const GLUSfloat normal[3]);
GLUSvoid GLUSAPIENTRY glusVector2Reflectf(GLUSfloat result[2], const GLUSfloat incident[2], const GLUSfloat normal[2]);
GLUSvoid GLUSAPIENTRY glusVector3Refractf(GLUSfloat result[3], const GLUSfloat incident[3], const GLUSfloat normal[3], const float eta);
GLUSvoid GLUSAPIENTRY glusVector2Refractf(GLUSfloat result[2], const GLUSfloat incident[2], const GLUSfloat normal[2], const float eta);
GLUSfloat GLUSAPIENTRY glusVector3Fresnelf(const GLUSfloat incident[3], const GLUSfloat normal[3], const GLUSfloat R0);
GLUSfloat GLUSAPIENTRY glusVector2Fresnelf(const GLUSfloat incident[2], const GLUSfloat normal[2], const GLUSfloat R0);
GLUSvoid GLUSAPIENTRY glusVectorNCopyc(GLUScomplex* result, const GLUScomplex* vector, const GLUSint n);
GLUSvoid GLUSAPIENTRY glusVectorNComplexToFloatc(GLUSfloat* result, const GLUScomplex* vector, const GLUSint n);
GLUSvoid GLUSAPIENTRY glusVectorNFloatToComplexc(GLUScomplex* result, const GLUSfloat* vector, const GLUSint n);
GLUSvoid GLUSAPIENTRY glusVectorNMultiplyScalarc(GLUScomplex* result, const GLUScomplex* vector, const GLUSint n, const GLUSfloat scalar);
GLUSvoid GLUSAPIENTRY glusVectorNConjugatec(GLUScomplex* result, const GLUScomplex* vector, const GLUSint n);
*/

//	aux
float	to_rad(float degrees);
float	to_deg(float radians);
float	map(t_rtf value, t_rtf range_orig[2], t_rtf range_dest[2]);
bool	normalize_value(t_rtf *value, t_rtf min, t_rtf max);
bool	is_maxf(float this, float that);
float	medf(float a, float b);
float	mixf(float a, float b, float t);
float	clamp(float value, float min, float max);

#endif
