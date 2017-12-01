#pragma once

class vec2 {
public:
	vec2();
	vec2(double x, double y);
	vec2(const vec2& v);
	vec2(const vec3& v);

	double x, y;
};

class vec3 {
public:
	vec3();
	vec3(double x, double y, double z);
	vec3(const vec2& v, double z);
	vec3(const vec3& v);

	double x, y, z;
};

inline double dot(const vec3& va, const vec3& vb) {
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

inline vec3 cross(const vec3& va, const vec3& vb) {
	return vec3(
		va.y * vb.z - va.z * vb.y,
		va.x * vb.z - va.z * vb.x,
		va.x * vb.y - va.y * vb.x
	);
}