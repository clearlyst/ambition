#pragma once

#include "../Math/Vector.hpp"
#include "../Math/QAngle.hpp"
#include "../Math/VMatrix.hpp"

class OverlayText_t;

class IVDebugOverlay
{
public:
	bool world_to_screen(const Vector& in, Vector& out)
	{
		using original_fn = int(__thiscall*)(IVDebugOverlay*, const Vector&, Vector&);
		int return_value = (*(original_fn**)this)[13](this, in, out);
		return static_cast<bool>(return_value != 1);
	}

	virtual void AddCapsuleOverlay(const Vector& mins, const Vector& max, float& radius, int r, int g, int b, int a, float duration, char unknown, char ignorez) = 0;

	bool screen_position(const Vector& in, Vector& out)
	{
		using original_fn = bool(__thiscall*)(IVDebugOverlay*, const Vector&, Vector&);
		return (*(original_fn**)this)[11](this, std::ref(in), std::ref(out));
	}
};