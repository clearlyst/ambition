#pragma once

#include "../valve_sdk/math/Vector.hpp"
#include "../valve_sdk/math/VMatrix.hpp"
#include "../valve_sdk/sdk.hpp"

namespace math 
{
	Vector vector_transform(const Vector& vector, const matrix3x4_t& matrix);
	void vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
	bool world_to_screen(const Vector& origin, Vector& screen);
	Vector calculate_angle(Vector src, Vector dst);
	Vector calculate_angle(const Vector& source, const Vector& destination, const Vector& view_angles);
	void angle_vectors(Vector& angles, Vector& forward);
	void vectors_angle(const Vector vecForward, Vector& vecAngles);
	float calculate_fov(const Vector& source, const Vector& destination, const Vector& viewangles);
	void start_movement_fix(CUserCmd* cmd);
	void end_movement_fix(CUserCmd* cmd);
	float normalize_yaw(float yaw);
	float float_random(float min, float max);
};