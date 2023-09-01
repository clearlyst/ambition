#pragma once

#include <sstream>
#include <DirectXMath.h>
#include <algorithm>
#include <limits>
#include <cmath>

#define RAD2DEG(x) DirectX::XMConvertToDegrees(x)
#define DEG2RAD(x) DirectX::XMConvertToRadians(x)

constexpr double M_PI = 3.14159265358979323846;
constexpr float M_RADPI = 57.295779513082f;
constexpr float M_PI_F = static_cast<float>(M_PI);

constexpr float RAD2DEG_2(const float x) 
{
    return (float)(x) * (float)(180.f / M_PI_F);
}

constexpr float DEG2RAD_2(const float x) 
{
    return (float)(x) * (float)(M_PI_F / 180.f);
}

class Vector
{
public:
    Vector(void)
    {
        Invalidate();
    }
    Vector(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
    }
    Vector(const float* clr)
    {
        x = clr[0];
        y = clr[1];
        z = clr[2];
    }

    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
    {
        x = ix; y = iy; z = iz;
    }

    bool IsValid() const
    {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    void clamp(void) 
    {
        x = std::clamp(x, -89.0f, 89.0f);
        y = std::clamp(std::remainder(y, 360.0f), -180.0f, 180.0f);
        z = std::clamp(z, -50.0f, 50.0f);
    }

    Vector clamped() 
    {
        Vector clamped = *this;
        clamped.clamp();
        return clamped;
    }

    void Invalidate()
    {
        x = y = z = std::numeric_limits<float>::infinity();
    }

    float& operator[](int i)
    {
        return ((float*)this)[i];
    }
    float operator[](int i) const
    {
        return ((float*)this)[i];
    }

    bool IsZero()
    {
        return (!x && !y && !z);
    }

    void Zero()
    {
        x = y = z = 0.0f;
    }

    bool operator==(const Vector& src) const
    {
        return (src.x == x) && (src.y == y) && (src.z == z);
    }
    bool operator!=(const Vector& src) const
    {
        return (src.x != x) || (src.y != y) || (src.z != z);
    }

    Vector& operator+=(const Vector& v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    Vector& operator-=(const Vector& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    Vector& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }
    Vector& operator*=(const Vector& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    Vector& operator/=(const Vector& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    Vector& operator+=(float fl)
    {
        x += fl;
        y += fl;
        z += fl;
        return *this;
    }
    Vector& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        z /= fl;
        return *this;
    }
    Vector& operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        z -= fl;
        return *this;
    }

    Vector operator+(const float add) const
    {
        return Vector(this->x + add, this->y + add, this->z + add);
    }

    Vector operator-(const float subtract) const
    {
        return Vector(this->x - subtract, this->y - subtract, this->z - subtract);
    }

    void NormalizeInPlace()
    {
        *this = Normalized();
    }

    float NormalizeFloat()
    {
        Vector res = *this;
        float l = res.Length();
        if (l != 0.0f)
        {
            res /= l;
        }
        else
        {
            res.x = res.y = res.z = 0.0f;
        }
        return l;
    }

    Vector Normalize()
    {

        this->x = std::clamp(this->x, -89.f, 89.f);

        float rot;
        float& angle = this->y;
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

        this->z = 0.f;

        return *this;
    }

    Vector Normalized() const
    {
        Vector res = *this;
        float l = res.Length();
        if(l != 0.0f) {
            res /= l;
        } else {
            res.x = res.y = res.z = 0.0f;
        }
        return res;
    }

    static auto fromAngleAll(const Vector& angle, Vector* forward, Vector* right, Vector* up)
    {
        float sr = std::sin(DEG2RAD_2(angle.z))
            , sp = std::sin(DEG2RAD_2(angle.x))
            , sy = std::sin(DEG2RAD_2(angle.y))
            , cr = std::cos(DEG2RAD_2(angle.z))
            , cp = std::cos(DEG2RAD_2(angle.x))
            , cy = std::cos(DEG2RAD_2(angle.y));

        if (forward)
        {
            forward->x = cp * cy;
            forward->y = cp * sy;
            forward->z = -sp;
        }

        if (right)
        {
            right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
            right->y = (-1 * sr * sp * sy + -1 * cr * cy);
            right->z = -1 * sr * cp;
        }

        if (up)
        {
            up->x = (cr * sp * cy + -sr * -sy);
            up->y = (cr * sp * sy + -sr * cy);
            up->z = cr * cp;
        }
    }

    static auto fromAngle(const Vector& angle) noexcept
    {
        return Vector{ std::cos(DEG2RAD(angle.x)) * std::cos(DEG2RAD(angle.y)), std::cos(DEG2RAD(angle.x)) * std::sin(DEG2RAD(angle.y)), -std::sin(DEG2RAD(angle.x)) };
    }

    auto toAngle() const noexcept
    {
        return Vector{ RAD2DEG(std::atan2(-z, std::hypot(x, y))),
                       RAD2DEG(std::atan2(y, x)),
                       0.0f };
    }

    bool is_zero(void) 
    {
        if (x == 0 && y == 0 && z == 0)
        {
            return true;
        }

        return false;
    }

    constexpr void normalize() noexcept
    {
        x = std::isfinite(x) ? std::remainder(x, 360.0f) : 0.0f;
        y = std::isfinite(y) ? std::remainder(y, 360.0f) : 0.0f;
        z = 0.0f;
    }

    float DistTo(const Vector &vOther) const
    {
        Vector delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.Length();
    }

    float DistToSqr(const Vector &vOther) const
    {
        Vector delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.LengthSqr();
    }

    float Dot(const Vector& vOther) const
    {
        return (x*vOther.x + y*vOther.y + z*vOther.z);
    }

    float Length() const
    {
        return sqrt(x*x + y*y + z*z);
    }

    float LengthSqr(void) const
    {
        return (x*x + y*y + z*z);
    }

    float Length2D() const
    {
        return sqrt(x*x + y*y);
    }

    Vector& operator=(const Vector &vOther)
    {
        x = vOther.x; y = vOther.y; z = vOther.z;
        return *this;
    }

    Vector Vector::operator-(void) const
    {
        return Vector(-x, -y, -z);
    }
    Vector Vector::operator+(const Vector& v) const
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }
    Vector Vector::operator-(const Vector& v) const
    {
        return Vector(x - v.x, y - v.y, z - v.z);
    }
    Vector Vector::operator*(float fl) const
    {
        return Vector(x * fl, y * fl, z * fl);
    }
    Vector Vector::operator*(const Vector& v) const
    {
        return Vector(x * v.x, y * v.y, z * v.z);
    }
    Vector Vector::operator/(float fl) const
    {
        return Vector(x / fl, y / fl, z / fl);
    }
    Vector Vector::operator/(const Vector& v) const
    {
        return Vector(x / v.x, y / v.y, z / v.z);
    }

    float x, y, z;
};

inline Vector operator*(float lhs, const Vector& rhs)
{
    return rhs * lhs;
}
inline Vector operator/(float lhs, const Vector& rhs)
{
    return rhs / lhs;
}

class __declspec(align(16)) VectorAligned : public Vector
{
public:
    inline VectorAligned(void) {};
    inline VectorAligned(float X, float Y, float Z)
    {
        Init(X, Y, Z);
    }

public:
    explicit VectorAligned(const Vector &vOther)
    {
        Init(vOther.x, vOther.y, vOther.z);
    }

    VectorAligned& operator=(const Vector &vOther)
    {
        Init(vOther.x, vOther.y, vOther.z);
        return *this;
    }

    VectorAligned& operator=(const VectorAligned &vOther)
    {
        Init(vOther.x, vOther.y, vOther.z);
        return *this;
    }

    float w;
};