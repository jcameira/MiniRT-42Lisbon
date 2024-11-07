/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_advanced.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:34:13 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/10/28 21:15:47 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Cross Product: vector that is perpendicular to two 3D vectors
void	vec3_crossf(t_rtf result[3], const t_rtf vector0[3],
	const t_rtf vector1[3])
{
	result[0] = vector0[1] * vector1[2] - vector0[2] * vector1[1];
	result[1] = vector0[2] * vector1[0] - vector0[0] * vector1[2];
	result[2] = vector0[0] * vector1[1] - vector0[1] * vector1[0];
}

// Angle Between Vectors: the angle between two 3D vectors.
float	vec3_angle(const float vector0[3], const float vector1[3])
{
	float	dot;
	float	len0;
	float	len1;

	dot = vec3_dotf(vector0, vector1);
	len0 = vec3_lenf(vector0);
	len1 = vec3_lenf(vector1);
	return (acos(dot / (len0 * len1)));
}

// Projection of vector0 onto vector1
// vector0[3]: The vector to be projected.
// vector1[3]: The vector onto which vector0 is projected.
void	vec3_project(t_rtf result[3], const t_rtf vector0[3],
	const t_rtf vector1[3])
{
	float	dot;
	float	len1_sq;
	float	dot_divided_by_len1_sq;

	dot = vec3_dotf(vector0, vector1);
	len1_sq = vec3_dotf(vector1, vector1);
	dot_divided_by_len1_sq = dot / len1_sq;
	result[0] = dot_divided_by_len1_sq * vector1[0];
	result[1] = dot_divided_by_len1_sq * vector1[1];
	result[2] = dot_divided_by_len1_sq * vector1[2];
}

// TODO take whats needed, if any
// NOTHING TO SEE HERE, MOVE ALONG

/*
// GLUSvoid GLUSAPIENTRY glusVector3GetQuaternionf(GLUSfloat result[4], const GLUSfloat vector[3])
// {
// 	result[0] = vector[0];
// 	result[1] = vector[1];
// 	result[2] = vector[2];
// 	result[3] = 0.0f;
// }

// GLUSvoid GLUSAPIENTRY glusVector3GetPoint4f(GLUSfloat result[4], const GLUSfloat vector[3])
// {
// 	result[0] = vector[0];
// 	result[1] = vector[1];
// 	result[2] = vector[2];
// 	result[3] = 1.0f;
// }


GLUSvoid GLUSAPIENTRY glusVector2GetPoint3f(GLUSfloat result[3], const GLUSfloat vector[2])
{
	result[0] = vector[0];
	result[1] = vector[1];
	result[2] = 1.0f;
}

// glusVector3GramSchmidtOrthof performs the Gram-Schmidt orthogonalization process
// on two 3D vectors. Specifically, it orthogonalizes vector v with respect
// to vector u and stores the result in result.
// This is useful in various applications such as numerical linear algebra,
// computer graphics, and signal processing.
GLUSboolean GLUSAPIENTRY glusVector3GramSchmidtOrthof(GLUSfloat result[3], const GLUSfloat u[3], const GLUSfloat v[3])
{
	GLUSfloat uProjV[3];

	GLUSfloat vDotU;

	GLUSfloat uDotU = glusVector3Dotf(u, u);

	if (uDotU == 0.0f)
	{
		return GLUS_FALSE;
	}

	vDotU = glusVector3Dotf(v, u);

	uProjV[0] = u[0] * vDotU / uDotU;
	uProjV[1] = u[1] * vDotU / uDotU;
	uProjV[2] = u[2] * vDotU / uDotU;

	glusVector3SubtractVector3f(result, v, uProjV);

	return GLUS_TRUE;
}

GLUSboolean GLUSAPIENTRY glusVector2GramSchmidtOrthof(GLUSfloat result[2], const GLUSfloat u[2], const GLUSfloat v[2])
{
	GLUSfloat uProjV[2];

	GLUSfloat vDotU;

	GLUSfloat uDotU = glusVector2Dotf(u, u);

	if (uDotU == 0.0f)
	{
		return GLUS_FALSE;
	}

	vDotU = glusVector2Dotf(v, u);

	uProjV[0] = u[0] * vDotU / uDotU;
	uProjV[1] = u[1] * vDotU / uDotU;

	glusVector2SubtractVector2f(result, v, uProjV);

	return GLUS_TRUE;
}

// The selected function glusVector3Reflectf calculates the reflection of an incident vector off a surface with a given normal vector. This is commonly used in computer graphics for simulating reflections of light or other vectors.
// result[3]: An array to store the resulting reflected vector.
// incident[3]: The incident vector (the vector that hits the surface).
// normal[3]: The normal vector of the surface (perpendicular to the surface at the point of incidence).

GLUSvoid GLUSAPIENTRY glusVector3Reflectf(GLUSfloat result[3], const GLUSfloat incident[3], const GLUSfloat normal[3])
{
	glusVector3MultiplyScalarf(result, normal, 2.0f * glusVector3Dotf(normal, incident));

	glusVector3SubtractVector3f(result, incident, result);
}

GLUSvoid GLUSAPIENTRY glusVector2Reflectf(GLUSfloat result[2], const GLUSfloat incident[2], const GLUSfloat normal[2])
{
	glusVector2MultiplyScalarf(result, normal, 2.0f * glusVector2Dotf(normal, incident));

	glusVector2SubtractVector2f(result, incident, result);
}


// The selected function glusVector3Refractf calculates the refraction of an incident vector through a surface with a given normal vector, based on Snell's law. This is commonly used in computer graphics to simulate the bending of light as it passes through different media, such as from air to water.
// result[3]: An array to store the resulting refracted vector.
// incident[3]: The incident vector (the vector that hits the surface).
// normal[3]: The normal vector of the surface (perpendicular to the surface at the point of incidence).
// eta: The ratio of the indices of refraction of the two media (e.g., from air to water).
GLUSvoid GLUSAPIENTRY glusVector3Refractf(GLUSfloat result[3], const GLUSfloat incident[3], const GLUSfloat normal[3], const float eta)
{
	// see http://www.opengl.org/sdk/docs/manglsl/xhtml/refract.xml
	// see http://en.wikipedia.org/wiki/Snell%27s_law
	// see http://www.hugi.scene.org/online/coding/hugi%2023%20-%20torefrac.htm for a and b vector.
	// In this implementation, the incident vector points into the interface. So the sings do change.

	GLUSfloat nDotI = glusVector3Dotf(normal, incident);

	GLUSfloat k = 1.0f - eta * eta * (1.0f - nDotI * nDotI);

	if (k < 0.0f)
	{
		result[0] = 0.0f;
		result[1] = 0.0f;
		result[2] = 0.0f;
	}
	else
	{
		GLUSfloat a[3];
		GLUSfloat b[3];

		glusVector3MultiplyScalarf(a, incident, eta);

		glusVector3MultiplyScalarf(b, normal, eta * nDotI + sqt_rtf(k));

		glusVector3SubtractVector3f(result, a, b);
	}
}

GLUSvoid GLUSAPIENTRY glusVector2Refractf(GLUSfloat result[2], const GLUSfloat incident[2], const GLUSfloat normal[2], const float eta)
{
	GLUSfloat nDotI = glusVector2Dotf(normal, incident);

	GLUSfloat k = 1.0f - eta * eta * (1.0f - nDotI * nDotI);

	if (k < 0.0f)
	{
		result[0] = 0.0f;
		result[1] = 0.0f;
	}
	else
	{
		GLUSfloat a[2];
		GLUSfloat b[2];

		glusVector2MultiplyScalarf(a, incident, eta);

		glusVector2MultiplyScalarf(b, normal, eta * nDotI + sqt_rtf(k));

		glusVector2SubtractVector2f(result, a, b);
	}
}

// The selected function glusVector3Fresnelf calculates the Fresnel reflection coefficient using Schlick's approximation. This coefficient determines the amount of light that is reflected off a surface at a given angle, which is important in computer graphics for simulating realistic reflections.
// incident[3]: The incident vector (the vector that hits the surface).
// normal[3]: The normal vector of the surface (perpendicular to the surface at the point of incidence).
// R0: The reflection coefficient at normal incidence (when the incident vector is perpendicular to the surface).
// Returns: The Fresnel reflection coefficient.
GLUSfloat GLUSAPIENTRY glusVector3Fresnelf(const GLUSfloat incident[3], const GLUSfloat normal[3], const GLUSfloat R0)
{
	// see http://en.wikipedia.org/wiki/Schlick%27s_approximation

	GLUSfloat negIncident[3];

	glusVector3MultiplyScalarf(negIncident, incident, -1.0f);

	return R0 + (1.0f - R0) * powf(1.0f - glusVector3Dotf(negIncident, normal), 5.0f);
}

GLUSfloat GLUSAPIENTRY glusVector2Fresnelf(const GLUSfloat incident[2], const GLUSfloat normal[2], const GLUSfloat R0)
{
	GLUSfloat negIncident[2];

	glusVector2MultiplyScalarf(negIncident, incident, -1.0f);

	return R0 + (1.0f - R0) * powf(1.0f - glusVector2Dotf(negIncident, normal), 5.0f);
}

//

GLUSvoid GLUSAPIENTRY glusVectorNCopyc(GLUScomplex* result, const GLUScomplex* vector, const GLUSint n)
{
	GLUSint i;

	for (i = 0; i < n; i++)
	{
		result[i] = vector[i];
	}
}

GLUSvoid GLUSAPIENTRY glusVectorNComplexToFloatc(GLUSfloat* result, const GLUScomplex* vector, const GLUSint n)
{
	GLUSint i;

	for (i = 0; i < n; i++)
	{
		result[2 * i + 0] = vector[i].real;
		result[2 * i + 1] = vector[i].imaginary;
	}
}

GLUSvoid GLUSAPIENTRY glusVectorNFloatToComplexc(GLUScomplex* result, const GLUSfloat* vector, const GLUSint n)
{
	GLUSint i;

	for (i = 0; i < n; i++)
	{
		result[i].real = vector[2 * i + 0];
		result[i].imaginary = vector[2 * i + 1];
	}
}

GLUSvoid GLUSAPIENTRY glusVectorNMultiplyScalarc(GLUScomplex* result, const GLUScomplex* vector, const GLUSint n, const GLUSfloat scalar)
{
	GLUSint i;

	for (i = 0; i < n; i++)
	{
		glusComplexMultiplyScalarc(&result[i], &vector[i], scalar);
	}
}

GLUSvoid GLUSAPIENTRY glusVectorNConjugatec(GLUScomplex* result, const GLUScomplex* vector, const GLUSint n)
{
	GLUSint i;

	for (i = 0; i < n; i++)
	{
		glusComplexConjugatec(&result[i], &vector[i]);
	}
}

*/
