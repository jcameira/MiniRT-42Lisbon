/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/21 18:08:32 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTOR_H
# define RT_VECTOR_H

typedef float	rtf;
typedef double	rtd;

//	vector
//	standard
void	vec3_copyf(rtf result[3], const rtf vector[3]);
void	vec2_copyf(rtf result[2], const rtf vector[2]);
void	vec3_addf(rtf result[3], const rtf vector0[3], const rtf vector1[3]);
void	vec2_addf(rtf result[2], const rtf vector0[2], const rtf vector1[2]);
void	vec3_subf(rtf result[3], const rtf vector0[3], const rtf vector1[3]);
void	vec2_subf(rtf result[2], const rtf vector0[2], const rtf vector1[2]);
float	vec3_dotf(const rtf vector0[3], const rtf vector1[3]);
float	vec2_dotf(const rtf vector0[2], const rtf vector1[2]);
void	vec3_scalef(rtf result[3], const rtf vector[3], const rtf scalar);
void	vec2_scalef(rtf result[2], const rtf vector[2], const rtf scalar);
float	vec3_lenf(const rtf vector[3]);
float	vec2_lenf(const rtf vector[2]);
bool	vec3_normalizef(rtf vector[3]);
bool	vec2_normalizef(rtf vector[2]);

//	advanced
void	vec3_crossf(rtf result[3], const rtf vector0[3], const rtf vector1[3]);
float	vec3_angle(const float vector0[3], const float vector1[3]);
void	vec3_project(rtf result[3], const rtf vector0[3], const rtf vector1[3]);
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
float	map(rtf value, rtf range_orig[2], rtf range_dest[2]);
bool	normalize_value(rtf *value, rtf min, rtf max);
bool	is_maxf(float this, float that);
float	medf(float a, float b);
float	mixf(float a, float b, float t);
float clamp(float value, float min, float max);

#endif
