#pragma once
#include "stdafx.h"

class Vec4 {
public:
    Vec4();
    Vec4(double x, double y, double z, double w);
    ~Vec4();

    double x;
    double y;
    double z;
    double w;

    Vec4 operator+(const Vec4& rhs) const;
    Vec4 operator-(const Vec4& rhs) const;

    Vec4 operator+(const double rhs) const;
    Vec4 operator-(const double rhs) const;

    double operator*(const Vec4& rhs) const;
    Vec4 operator*(const double rhs) const;

    BOOL operator==(const Vec4& rhs) const;
    BOOL operator!=(const Vec4& rhs) const;

private:
};