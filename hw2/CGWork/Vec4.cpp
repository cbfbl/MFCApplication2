#include "Vec4.h"

Vec4::Vec4() {}

Vec4::Vec4(double x, double y, double z, double w)
    : x(x)
    , y(y)
    , z(z)
    , w(w)
{
}
Vec4::~Vec4()
{
}

Vec4 Vec4::operator+(const Vec4& rhs) const
{
    return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}
Vec4 Vec4::operator-(const Vec4& rhs) const
{
    return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vec4 Vec4::operator+(const double rhs) const
{
    return Vec4(x + rhs, y + rhs, z + rhs, w + rhs);
}
Vec4 Vec4::operator-(const double rhs) const
{
    return Vec4(x - rhs, y - rhs, z - rhs, w - rhs);
}

double Vec4::operator*(const Vec4& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}
Vec4 Vec4::operator*(const double rhs) const
{
    return Vec4(x * rhs, y * rhs, z * rhs, w * rhs);
}


Vec4 Vec4::cross(const Vec4& rhs) const
{
    return Vec4(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x, 0);
}

Vec4 Vec4::normalize() const
{
    double sum = x + y + z;
    return Vec4(x / sum, y / sum, z / sum, w);
}


BOOL Vec4::operator==(const Vec4& rhs) const
{
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

BOOL Vec4::operator!=(const Vec4& rhs) const
{
    return !(*this == rhs);
}

