#pragma once
#include <algorithm>
#include <DirectXMath.h>

#define RAD2DEG(x) DirectX::XMConvertToDegrees(x)
#define DEG2RAD(x) DirectX::XMConvertToRadians(x)

class QAngle
{
public:
    QAngle(void)
    {
        Init();
    }
    QAngle(float X, float Y, float Z)
    {
        Init(X, Y, Z);
    }
    QAngle(const float* clr)
    {
        Init(clr[0], clr[1], clr[2]);
    }

    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
    {
        pitch = ix;
        yaw = iy;
        roll = iz;
    }

    float operator[](int i) const
    {
        return ((float*)this)[i];
    }
    float& operator[](int i)
    {
        return ((float*)this)[i];
    }

    QAngle& operator+=(const QAngle& v)
    {
        pitch += v.pitch; yaw += v.yaw; roll += v.roll;
        return *this;
    }
    QAngle& operator-=(const QAngle& v)
    {
        pitch -= v.pitch; yaw -= v.yaw; roll -= v.roll;
        return *this;
    }
    QAngle& operator*=(float fl)
    {
        pitch *= fl;
        yaw *= fl;
        roll *= fl;
        return *this;
    }
    QAngle& operator*=(const QAngle& v)
    {
        pitch *= v.pitch;
        yaw *= v.yaw;
        roll *= v.roll;
        return *this;
    }
    QAngle& operator/=(const QAngle& v)
    {
        pitch /= v.pitch;
        yaw /= v.yaw;
        roll /= v.roll;
        return *this;
    }
    QAngle& operator+=(float fl)
    {
        pitch += fl;
        yaw += fl;
        roll += fl;
        return *this;
    }
    QAngle& operator/=(float fl)
    {
        pitch /= fl;
        yaw /= fl;
        roll /= fl;
        return *this;
    }
    QAngle& operator-=(float fl)
    {
        pitch -= fl;
        yaw -= fl;
        roll -= fl;
        return *this;
    }

    QAngle& operator=(const QAngle &vOther)
    {
        pitch = vOther.pitch; yaw = vOther.yaw; roll = vOther.roll;
        return *this;
    }

    QAngle operator-(void) const
    {
        return QAngle(-pitch, -yaw, -roll);
    }
    QAngle operator+(const QAngle& v) const
    {
        return QAngle(pitch + v.pitch, yaw + v.yaw, roll + v.roll);
    }
    QAngle operator-(const QAngle& v) const
    {
        return QAngle(pitch - v.pitch, yaw - v.yaw, roll - v.roll);
    }
    QAngle operator*(float fl) const
    {
        return QAngle(pitch * fl, yaw * fl, roll * fl);
    }
    QAngle operator*(const QAngle& v) const
    {
        return QAngle(pitch * v.pitch, yaw * v.yaw, roll * v.roll);
    }
    QAngle operator/(float fl) const
    {
        return QAngle(pitch / fl, yaw / fl, roll / fl);
    }
    QAngle operator/(const QAngle& v) const
    {
        return QAngle(pitch / v.pitch, yaw / v.yaw, roll / v.roll);
    }

    float Length() const
    {
        return sqrt(pitch*pitch + yaw*yaw + roll*roll);
    }
    float LengthSqr(void) const
    {
        return (pitch*pitch + yaw*yaw + roll*roll);
    }

    bool IsZero(float tolerance = 0.01f) const
    {
        return (pitch > -tolerance && pitch < tolerance &&
            yaw > -tolerance && yaw < tolerance &&
            roll > -tolerance && roll < tolerance);
    }

    float Length2D(void) const
    {
        float root = 0.0f;

        float sqst = pitch * pitch + yaw * yaw;

        __asm
        {
            sqrtss xmm0, sqst
            movss root, xmm0
        }

        return root;
    }

    void clamp() {
        while (this->pitch < -89.0f)
            this->pitch += 89.0f;

        if (this->pitch > 89.0f)
            this->pitch = 89.0f;

        while (this->yaw < -180.0f)
            this->yaw += 360.0f;

        while (this->yaw > 180.0f)
            this->yaw -= 360.0f;

        this->roll = 0.0f;
    }

    static auto fromAngle(const QAngle& angle) noexcept
    {
        return QAngle{ std::cos(DEG2RAD(angle.pitch)) * std::cos(DEG2RAD(angle.yaw)),
                       std::cos(DEG2RAD(angle.pitch)) * std::sin(DEG2RAD(angle.yaw)),
                      -std::sin(DEG2RAD(angle.pitch)) };
    }

    QAngle& normalize() noexcept
    {
        pitch = std::isfinite(pitch) ? std::remainder(pitch, 360.0f) : 0.0f;
        yaw = std::isfinite(yaw) ? std::remainder(yaw, 360.0f) : 0.0f;
        roll = 0.0f;
        return *this;
    }

    bool validator()
    {
        return this->pitch == 0.f && this->yaw == 0.f && this->roll == 0.f;
    }

    QAngle Normalizee()
    {

        this->pitch = std::clamp(this->pitch, -89.f, 89.f);

        float rot;
        float& angle = this->yaw;
        // bad number.
        if (!std::isfinite(angle)) {
            angle = 0.f;
            return *this;
        }

        // no need to normalize this angle.
        if (angle >= -180.f && angle <= 180.f)
            return *this;

        // get amount of rotations needed.
        rot = std::round(std::abs(angle / 360.f));

        // normalize.
        angle = (angle < 0.f) ? angle + (360.f * rot) : angle - (360.f * rot);

        this->roll = 0.f;

        return *this;
    }


    auto toAngle() const noexcept
    {
        return QAngle{ RAD2DEG(std::atan2(-roll, std::hypot(pitch, yaw))),
                       RAD2DEG(std::atan2(yaw, pitch)),
                       0.0f };
    }

	float Normalize() const
	{
		QAngle res = *this;
		float l = res.Length();
		if (l != 0.0f)
		{
			res /= l;
		}
		else
		{
			res[0] = res[1] = res[2] = 0.0f;
		}
		return l;
	}

    float pitch;
    float yaw;
    float roll;
};

inline QAngle operator*(float lhs, const QAngle& rhs)
{
    return rhs * lhs;
}
inline QAngle operator/(float lhs, const QAngle& rhs)
{
    return rhs / lhs;
}
