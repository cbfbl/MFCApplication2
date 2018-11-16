#pragma once

#include "Vec4.h"

class Mat4 {
public:
    Mat4();
    Mat4(Vec4 row0, Vec4 row1, Vec4 row2, Vec4 row3);
    ~Mat4();

    Vec4 rows[4];

    Mat4 operator+(const Mat4& rhs) const;
    Mat4 operator-(const Mat4& rhs) const;

    Mat4 operator+(const double rhs) const;
    Mat4 operator-(const double rhs) const;

    Mat4 operator*(const Mat4& rhs) const;
    Vec4 operator*(const Vec4& rhs) const;
    Mat4 operator*(const double rhs) const;

    BOOL operator==(const Mat4& rhs) const;
    BOOL operator!=(const Mat4& rhs) const;

    Mat4 Mat4::transpose() const;

private:
};