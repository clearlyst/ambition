#pragma once

#include <windows.h>
#include "../helpers/xor.hpp"
#include "../helpers/singleton.hpp"

class console : public singleton<console>
{
public:
	void initialize(const char* title);
	void release();

	template <typename ... Args>
	void log(char const* const format, Args const& ... args)
	{
    #ifdef _DEBUG
    		printf(format, args ...);
    #endif
	}
};