#include "math.hpp"

Vector originalAngle;
float originalForwardMove, originalSideMove;

#define M_PI		3.14159265358979323846
#define M_PI_F		((float)(M_PI))
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

void sin_cos(float r, float* s, float* c)
{
	*s = sin(r);
	*c = cos(r);
}

Vector math::vector_transform(const Vector& vector, const matrix3x4_t& matrix)
{
	return Vector(vector.Dot(matrix[0]) + matrix[0][3], vector.Dot(matrix[1]) + matrix[1][3], vector.Dot(matrix[2]) + matrix[2][3]);
}

void math::vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
{
	out[0] = in1.Dot(in2[0]) + in2[0][3];
	out[1] = in1.Dot(in2[1]) + in2[1][3];
	out[2] = in1.Dot(in2[2]) + in2[2][3];
}

bool math::world_to_screen(const Vector& origin, Vector& screen)
{
	static std::uintptr_t view_matrix;
	if (!view_matrix)
		view_matrix = *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(Utils::PatternScan2("client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9")) + 3) + 176;

	static const auto& matrix = *reinterpret_cast<VMatrix*>(view_matrix);

	const auto w = matrix.m[3][0] * origin.x + matrix.m[3][1] * origin.y + matrix.m[3][2] * origin.z + matrix.m[3][3];

	if (w < 0.001f)
	{
		return false;
	}

	int x, y;
	g_EngineClient->GetScreenSize(x, y);

	screen.x = static_cast<float>(x) / 2.0f;
	screen.y = static_cast<float>(y) / 2.0f;

	screen.x *= 1.0f + (matrix.m[0][0] * origin.x + matrix.m[0][1] * origin.y + matrix.m[0][2] * origin.z + matrix.m[0][3]) / w;
	screen.y *= 1.0f - (matrix.m[1][0] * origin.x + matrix.m[1][1] * origin.y + matrix.m[1][2] * origin.z + matrix.m[1][3]) / w;

	return true;
}

Vector math::calculate_angle(Vector src, Vector dst)
{
	Vector angles;

	Vector delta = src - dst;
	float hyp = delta.Length2D();

	angles.y = std::atanf(delta.y / delta.x) * 57.2957795131f;
	angles.x = std::atanf(-delta.z / hyp) * -57.2957795131f;
	angles.z = 0.0f;

	if (delta.x >= 0.0f)
		angles.y += 180.0f;

	return angles;
}

Vector math::calculate_angle(const Vector& source, const Vector& destination, const Vector& view_angles)
{
	Vector delta = source - destination;
	Vector angles;

	angles.x = RAD2DEG(atanf(delta.z / std::hypotf(delta.x, delta.y))) - view_angles.x;
	angles.y = RAD2DEG(atanf(delta.y / delta.x)) - view_angles.y;
	angles.z = 0.0f;

	if (delta.x >= 0.0)
	{
		angles.y += 180.0f;
	}

	angles.normalize();

	return angles;
}

void math::angle_vectors(Vector& angles, Vector& forward)
{
	float sp, sy, cp, cy;

	sin_cos(DEG2RAD(angles.y), &sy, &cy);
	sin_cos(DEG2RAD(angles.x), &sp, &cp);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

void math::vectors_angle(const Vector vecForward, Vector& vecAngles)
{
	float flTemp, flYaw, flPitch;

	if (vecForward.y == 0 && vecForward.x == 0)
	{
		flYaw = 0;

		flPitch = 90;

		if (vecForward.z > 0)
		{
			flPitch = 270;
		}
	}
	else
	{
		flYaw = (atan2(vecForward.y, vecForward.x) * 180 / DirectX::XM_PI);

		if (flYaw < 0)
		{
			flYaw += 360;
		}

		flTemp = sqrt(vecForward.x * vecForward.x + vecForward.y * vecForward.y);
		flPitch = (atan2(-vecForward.z, flTemp) * 180 / DirectX::XM_PI);

		if (flPitch < 0)
		{
			flPitch += 360;
		}
	}

	vecAngles.x = flPitch;
	vecAngles.y = flYaw;
	vecAngles.z = 0;
}

float math::calculate_fov(const Vector& source, const Vector& destination, const Vector& viewangles)
{
	auto angle = calculate_angle(source, destination, viewangles);
	auto fov = std::hypot(angle.x, angle.y);
	return fov;
}

void math::start_movement_fix(CUserCmd* cmd)
{
	originalAngle = cmd->viewangles;
	originalForwardMove = cmd->forwardmove;
	originalSideMove = cmd->sidemove;
}

void math::end_movement_fix(CUserCmd* cmd)
{
	float deltaViewAngles;
	float f1;
	float f2;

	if (originalAngle.y < 0.f)
		f1 = 360.0f + originalAngle.y;
	else
		f1 = originalAngle.y;

	if (cmd->viewangles.y < 0.0f)
		f2 = 360.0f + cmd->viewangles.y;
	else
		f2 = cmd->viewangles.y;

	if (f2 < f1)
		deltaViewAngles = abs(f2 - f1);
	else
		deltaViewAngles = 360.0f - abs(f1 - f2);

	deltaViewAngles = 360.0f - deltaViewAngles;

	cmd->forwardmove = cos(DEG2RAD(deltaViewAngles)) * originalForwardMove + cos(DEG2RAD(deltaViewAngles + 90.f)) * originalSideMove;
	cmd->sidemove = sin(DEG2RAD(deltaViewAngles)) * originalForwardMove + sin(DEG2RAD(deltaViewAngles + 90.f)) * originalSideMove;
}

float math::normalize_yaw(float yaw)
{
	if (!std::isfinite(yaw))
		return 0.0f;

	if (yaw >= -180.f && yaw <= 180.f)
		return yaw;

	const float rot = std::round(std::abs(yaw / 360.f));

	yaw = (yaw < 0.f) ? yaw + (360.f * rot) : yaw - (360.f * rot);
	return yaw;
}

float math::float_random(float min, float max)
{
	float scale = rand() / (float)RAND_MAX; 
	return min + scale * (max - min); 
}