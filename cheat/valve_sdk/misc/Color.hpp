#pragma once

#include <fstream>
#include <algorithm>

class color 
{
public:
	color()
	{
		*((int*)this) = 0;
	}

	color(int _r, int _g, int _b)
	{
		set(_r, _g, _b, 255);
	}

	color(int _r, int _g, int _b, int _a)
	{
		set(_r, _g, _b, _a);
	}

	color(float _r, float _g, float _b)
	{
		set(_r, _g, _b, 1.0f);
	}

	color(float _r, float _g, float _b, float _a) : color(static_cast<int>(_r * 255.0f), static_cast<int>(_g * 255.0f), static_cast<int>(_b * 255.0f), static_cast<int>(_a * 255.0f))
	{
		set(_r, _g, _b, _a);
	}

	void set(int _r, int _g, int _b, int _a)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void set(float _r, float _g, float _b, float _a)
	{
		_color[0] = static_cast<unsigned char>(_r * 255.0f);
		_color[1] = static_cast<unsigned char>(_g * 255.0f);
		_color[2] = static_cast<unsigned char>(_b * 255.0f);
		_color[3] = static_cast<unsigned char>(_a * 255.0f);
	}

	void get(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	unsigned char get_raw() const
	{
		return *(unsigned char*)this;
	}

	void set_raw(int color32)
	{
		*((int*)this) = color32;
	}

	inline int get_red() const
	{
		return _color[0];
	}

	inline int get_green() const
	{
		return _color[1];
	}

	inline int get_blue() const
	{
		return _color[2];
	}

	inline int get_alpha() const
	{
		return _color[3];
	}

	inline void set_red(int value)
	{
		_color[0] = value;
	}

	inline void set_green(int value)
	{
		_color[1] = value;
	}

	inline void set_blue(int value)
	{
		_color[2] = value;
	}

	inline void set_alpha(int value)
	{
		_color[3] = value;
	}

	unsigned char& operator[](int index)
	{
		return _color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return _color[index];
	}

	bool operator== (const color& rhs) const
	{
		return (*((int*)this) == *((int*)&rhs));
	}

	bool operator!= (const color& rhs) const
	{
		return !(operator==(rhs));
	}

	color& operator=(const color& rhs)
	{
		set_raw(rhs.get_raw());
		return *this;
	}
private:
	unsigned char _color[4];
};