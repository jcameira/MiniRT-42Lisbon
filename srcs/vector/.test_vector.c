
#include <minirt.h>

#define EPSILON 1e-6

// Helper function to compare two vectors
int compare_vectors(const rtf *v1, const rtf *v2, int size) {
	for (int i = 0; i < size; i++) {
		if (fabs(v1[i] - v2[i]) > EPSILON) {
			return 0;
		}
	}
	return 1;
}

// Test for vec3_copyf
void test_vec3_copyf(void) {
	rtf vector[3] = {1.0f, 2.0f, 3.0f};
	rtf result[3];
	vec3_copyf(result, vector);
	printf("vec3_copyf: %s\n", compare_vectors(result, vector, 3) ? "PASSED" : "FAILED");
}

// Test for vec2_copyf
void test_vec2_copyf(void) {
	rtf vector[2] = {1.0f, 2.0f};
	rtf result[2];
	vec2_copyf(result, vector);
	printf("vec2_copyf: %s\n", compare_vectors(result, vector, 2) ? "PASSED" : "FAILED");
}

// Test for vec3_addf
void test_vec3_addf(void) {
	rtf vector0[3] = {1.0f, 2.0f, 3.0f};
	rtf vector1[3] = {4.0f, 5.0f, 6.0f};
	rtf result[3];
	rtf expected[3] = {5.0f, 7.0f, 9.0f};
	vec3_addf(result, vector0, vector1);
	printf("vec3_addf: %s\n", compare_vectors(result, expected, 3) ? "PASSED" : "FAILED");
}

// Test for vec2_addf
void test_vec2_addf(void) {
	rtf vector0[2] = {1.0f, 2.0f};
	rtf vector1[2] = {3.0f, 4.0f};
	rtf result[2];
	rtf expected[2] = {4.0f, 6.0f};
	vec2_addf(result, vector0, vector1);
	printf("vec2_addf: %s\n", compare_vectors(result, expected, 2) ? "PASSED" : "FAILED");
}

// Test for vec3_subf
void test_vec3_subf(void) {
	rtf vector0[3] = {4.0f, 5.0f, 6.0f};
	rtf vector1[3] = {1.0f, 2.0f, 3.0f};
	rtf result[3];
	rtf expected[3] = {3.0f, 3.0f, 3.0f};
	vec3_subf(result, vector0, vector1);
	printf("vec3_subf: %s\n", compare_vectors(result, expected, 3) ? "PASSED" : "FAILED");
}

// Test for vec2_subf
void test_vec2_subf(void) {
	rtf vector0[2] = {3.0f, 4.0f};
	rtf vector1[2] = {1.0f, 2.0f};
	rtf result[2];
	rtf expected[2] = {2.0f, 2.0f};
	vec2_subf(result, vector0, vector1);
	printf("vec2_subf: %s\n", compare_vectors(result, expected, 2) ? "PASSED" : "FAILED");
}

// Test for vec3_dotf
void test_vec3_dotf(void) {
	rtf vector0[3] = {1.0f, 2.0f, 3.0f};
	rtf vector1[3] = {4.0f, 5.0f, 6.0f};
	float result = vec3_dotf(vector0, vector1);
	float expected = 32.0f;
	printf("vec3_dotf: %s\n", fabs(result - expected) < EPSILON ? "PASSED" : "FAILED");
}

// Test for vec2_dotf
void test_vec2_dotf(void) {
	rtf vector0[2] = {1.0f, 2.0f};
	rtf vector1[2] = {3.0f, 4.0f};
	float result = vec2_dotf(vector0, vector1);
	float expected = 11.0f;
	printf("vec2_dotf: %s\n", fabs(result - expected) < EPSILON ? "PASSED" : "FAILED");
}

// Test for vec3_scalef
void test_vec3_scalef(void) {
	rtf vector[3] = {1.0f, 2.0f, 3.0f};
	rtf result[3];
	rtf expected[3] = {2.0f, 4.0f, 6.0f};
	vec3_scalef(result, vector, 2.0f);
	printf("vec3_scalef: %s\n", compare_vectors(result, expected, 3) ? "PASSED" : "FAILED");
}

// Test for vec2_scalef
void test_vec2_scalef(void) {
	rtf vector[2] = {1.0f, 2.0f};
	rtf result[2];
	rtf expected[2] = {2.0f, 4.0f};
	vec2_scalef(result, vector, 2.0f);
	printf("vec2_scalef: %s\n", compare_vectors(result, expected, 2) ? "PASSED" : "FAILED");
}

// Test for vec3_lenf
void test_vec3_lenf(void) {
	rtf vector[3] = {3.0f, 4.0f, 0.0f};
	float length = vec3_lenf(vector);
	printf("vec3_lenf: %s\n", fabs(length - 5.0f) < EPSILON ? "PASSED" : "FAILED");
}

// Test for vec2_lenf
void test_vec2_lenf(void) {
	rtf vector[2] = {3.0f, 4.0f};
	float length = vec2_lenf(vector);
	printf("vec2_lenf: %s\n", fabs(length - 5.0f) < EPSILON ? "PASSED" : "FAILED");
}

// Test for vec3_normalizef
void test_vec3_normalizef(void) {
	rtf vector[3] = {3.0f, 4.0f, 0.0f};
	rtf expected[3] = {0.6f, 0.8f, 0.0f};
	if (vec3_normalizef(vector) && compare_vectors(vector, expected, 3)) {
		printf("vec3_normalizef: PASSED\n");
	} else {
		printf("vec3_normalizef: FAILED\n");
	}

	rtf zero_vector[3] = {0.0f, 0.0f, 0.0f};
	if (!vec3_normalizef(zero_vector)) {
		printf("vec3_normalizef (zero vector): PASSED\n");
	} else {
		printf("vec3_normalizef (zero vector): FAILED\n");
	}
}

// Test for vec2_normalizef
void test_vec2_normalizef(void) {
	rtf vector[2] = {3.0f, 4.0f};
	rtf expected[2] = {0.6f, 0.8f};
	if (vec2_normalizef(vector) && compare_vectors(vector, expected, 2)) {
		printf("vec2_normalizef: PASSED\n");
	} else {
		printf("vec2_normalizef: FAILED\n");
	}

	rtf zero_vector[2] = {0.0f, 0.0f};
	if (!vec2_normalizef(zero_vector)) {
		printf("vec2_normalizef (zero vector): PASSED\n");
	} else {
		printf("vec2_normalizef (zero vector): FAILED\n");
	}
}

// Test for vec3_crossf
void test_vec3_crossf(void) {
	rtf vector0[3] = {1.0f, 0.0f, 0.0f};
	rtf vector1[3] = {0.0f, 1.0f, 0.0f};
	rtf result[3];
	rtf expected[3] = {0.0f, 0.0f, 1.0f};
	vec3_crossf(result, vector0, vector1);
	printf("vec3_crossf: %s\n", compare_vectors(result, expected, 3) ? "PASSED" : "FAILED");
}




// Test for vec3_angle
void test_vec3_angle(void) {
	rtf vector0[3] = {1.0f, 0.0f, 0.0f};
	rtf vector1[3] = {0.0f, 1.0f, 0.0f};
	float angle = vec3_angle(vector0, vector1);
	float expected = M_PI / 2; // 90 degrees
	printf("vec3_angle: %s\n", fabs(angle - expected) < EPSILON ? "PASSED" : "FAILED");
}

// Test for vec3_project
void test_vec3_project(void) {
	rtf vector0[3] = {2.0f, 3.0f, 4.0f};
	rtf vector1[3] = {1.0f, 0.0f, 0.0f};
	rtf result[3];
	rtf expected[3] = {2.0f, 0.0f, 0.0f};
	vec3_project(result, vector0, vector1);
	printf("vec3_project: %s\n", compare_vectors(result, expected, 3) ? "PASSED" : "FAILED");
}

// Test for to_rad
void test_to_rad(void) {
	float degrees = 180.0f;
	float radians = to_rad(degrees);
	float expected = M_PI;
	printf("to_rad: %s\n", fabs(radians - expected) < EPSILON ? "PASSED" : "FAILED");
}

// Test for to_deg
void test_to_deg(void) {
	float radians = M_PI;
	float degrees = to_deg(radians);
	float expected = 180.0f;
	printf("to_deg: %s\n", fabs(degrees - expected) < EPSILON ? "PASSED" : "FAILED");
}

// Test for map
void test_map(void) {
	rtf value = 5.0f;
	rtf range_orig[2] = {0.0f, 10.0f};
	rtf range_dest[2] = {0.0f, 100.0f};
	float mapped_value = map(value, range_orig, range_dest);
	float expected = 50.0f;
	printf("map: %s\n", fabs(mapped_value - expected) < EPSILON ? "PASSED" : "FAILED");
}

// Test for normalize_value
void test_normalize_value(void) {
	rtf value = 5.0f;
	rtf min = 0.0f;
	rtf max = 10.0f;
	if (normalize_value(&value, min, max) && fabs(value - 0.5f) < EPSILON) {
		printf("normalize_value: PASSED\n");
	} else {
		printf("normalize_value: FAILED\n");
	}

	rtf zero_value = 0.0f;
	if (!normalize_value(&zero_value, min, max)) {
		printf("normalize_value (zero value): PASSED\n");
	} else {
		printf("normalize_value (zero value): FAILED\n");
	}

	rtf equal_min_max_value = 5.0f;
	if (!normalize_value(&equal_min_max_value, 5.0f, 5.0f)) {
		printf("normalize_value (equal min and max): PASSED\n");
	} else {
		printf("normalize_value (equal min and max): FAILED\n");
	}
}


void test_medf()
{
	float a = 10.0f;
	float b = 20.0f;
	float result = medf(a, b);
	printf("med(%f, %f) = %f\n", a, b, result);
	a = 0.0f;
	b = 0.0f;
	result = medf(a, b);
	printf("med(%f, %f) = %f\n", a, b, result);
}

void test_mixf()
{
	float a = 10.0f;
	float b = 20.0f;
	float t = 0.8f;
	float result = mixf(a, b, t);
	printf("mix(%f, %f, %f) = %f\n", a, b, t, result);
	a = 0.0f;
	b = 0.0f;
	result = mixf(a, b, t);
	printf("mix(%f, %f, %f) = %f\n", a, b, t, result);
	a = 10.0f;
	b = 20.0f;
	t = 0.0f;
	result = mixf(a, b, t);
	printf("mix(%f, %f, %f) = %f\n", a, b, t, result);
}

void test_clamp()
{
	float value = 15.0f;
	float min = 10.0f;
	float max = 20.0f;
	float result = clamp(value, min, max);
	printf("clamp(%f, %f, %f) = %f\n", value, min, max, result);
	min = 16.0f;
	max = 20.0f;
	result = clamp(value, min, max);
	printf("clamp(%f, %f, %f) = %f\n", value, min, max, result);
	min = 10.0f;
	max = 14.0f;
	result = clamp(value, min, max);
	printf("clamp(%f, %f, %f) = %f\n", value, min, max, result);
}

// Main function to run all tests
int main() {
	printf("vector.c tests\n");
	test_vec3_copyf();
	test_vec2_copyf();
	test_vec3_addf();
	test_vec2_addf();
	test_vec3_subf();
	test_vec2_subf();
	test_vec3_dotf();
	test_vec2_dotf();
	test_vec3_scalef();
	test_vec2_scalef();
	test_vec3_lenf();
	test_vec2_lenf();
	test_vec3_normalizef();
	test_vec2_normalizef();
	printf("vector_advanced.c tests\n");
	test_vec3_crossf();
	test_vec3_crossf();
	test_vec3_angle();
	test_vec3_project();
	printf("vector_aux.c tests\n");
	test_to_rad();
	test_to_deg();
	test_map();
	test_normalize_value();
	test_mixf();
	test_medf();
	test_clamp();

	return 0;
}

// gcc -o test_vector test_vector.c vector.c vector_advanced.c vector_aux.c -lm
// ./test_vector

/*
int compare_vectors(const rtf *v1, const rtf *v2, int size)
compare_vectors: Compares two vectors element-wise
with a tolerance defined by EPSILON.
*/
