#include "Mat4.h"
#include <assert.h>

Mat4::Mat4() {}

Mat4::Mat4(Vec4 row0, Vec4 row1, Vec4 row2, Vec4 row3)
{
    rows[0] = row0;
    rows[1] = row1;
    rows[2] = row2;
    rows[3] = row3;
}

Mat4::~Mat4()
{
}

Mat4 Mat4::operator+(const Mat4& rhs) const
{
    return Mat4(
        rows[0] + rhs.rows[0],
        rows[1] + rhs.rows[1],
        rows[2] + rhs.rows[2],
        rows[3] + rhs.rows[3]);
}
Mat4 Mat4::operator-(const Mat4& rhs) const
{
    return Mat4(
        rows[0] - rhs.rows[0],
        rows[1] - rhs.rows[1],
        rows[2] - rhs.rows[2],
        rows[3] - rhs.rows[3]);
}
Mat4 Mat4::operator+(const double rhs) const
{
    return Mat4(
        rows[0] + rhs,
        rows[1] + rhs,
        rows[2] + rhs,
        rows[3] + rhs);
}
Mat4 Mat4::operator-(const double rhs) const
{
    return Mat4(
        rows[0] - rhs,
        rows[1] - rhs,
        rows[2] - rhs,
        rows[3] - rhs);
}

Mat4 Mat4::operator*(const Mat4& rhs) const
{
    Mat4 rhsT = rhs.transpose();
    return Mat4(
        Vec4(rows[0] * rhsT.rows[0], rows[0] * rhsT.rows[1], rows[0] * rhsT.rows[2], rows[0] * rhsT.rows[3]),
        Vec4(rows[1] * rhsT.rows[0], rows[1] * rhsT.rows[1], rows[1] * rhsT.rows[2], rows[1] * rhsT.rows[3]),
        Vec4(rows[2] * rhsT.rows[0], rows[2] * rhsT.rows[1], rows[2] * rhsT.rows[2], rows[2] * rhsT.rows[3]),
        Vec4(rows[3] * rhsT.rows[0], rows[3] * rhsT.rows[1], rows[3] * rhsT.rows[2], rows[3] * rhsT.rows[3]));
}
Vec4 Mat4::operator*(const Vec4& rhs) const
{
    return Vec4(
        rows[0] * rhs,
        rows[1] * rhs,
        rows[2] * rhs,
        rows[3] * rhs);
}
Mat4 Mat4::operator*(const double rhs) const
{
    return Mat4(
        rows[0] * rhs,
        rows[1] * rhs,
        rows[2] * rhs,
        rows[3] * rhs);
}

BOOL Mat4::operator==(const Mat4& rhs) const {
    for (int i = 0; i < 4; i++) {
        if (rows[i] != rhs.rows[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL Mat4::operator!=(const Mat4& rhs) const
{
    return !(*this == rhs);
}

Mat4 Mat4::transpose() const
{
    return Mat4(
        Vec4(rows[0].x, rows[1].x, rows[2].x, rows[3].x),
        Vec4(rows[0].y, rows[1].y, rows[2].y, rows[3].y),
        Vec4(rows[0].z, rows[1].z, rows[2].z, rows[3].z),
        Vec4(rows[0].w, rows[1].w, rows[2].w, rows[3].w));
}

void verify()
{
    Mat4 m1 = Mat4(
        Vec4(-1, 3, -4, 6),
        Vec4(11, 3, 4, 5),
        Vec4(1, -3, 4, 87),
        Vec4(-3, -3, 4, -9));

    Mat4 m2 = Mat4(
        Vec4(41, 3, 4, 55),
        Vec4(-1, 3, 44, 5),
        Vec4(-30, 3, 4, -91),
        Vec4(10, 17, 4, -2));

    Vec4 v1 = Vec4(-1, -9, 7, 32);
    Vec4 v2 = Vec4(0, 91, -30, 6);

    assert(v1 + v2 == Vec4(-1, 82, -23, 38));
    assert(v1 - v2 == Vec4(-1, -100, 37, 26));
    assert(v1 + 70 == Vec4(69, 61, 77, 102));
    assert(v2 - 10 == Vec4(-10, 81, -40, -4));
    assert(v1 * v2 == -837);

    assert(m1.transpose() == Mat4(
        Vec4(-1, 11, 1, -3),
        Vec4(3, 3, -3, -3),
        Vec4(-4, 4, 4, 4),
        Vec4(6, 5, 87, -9)));

    assert(m1 + 30 == Mat4(
        Vec4(29, 33, 26, 36), 
        Vec4(41, 33, 34, 35), 
        Vec4(31, 27, 34, 117), 
        Vec4(27, 27, 34, 21)));

    assert(m2 - 11 == Mat4(
        Vec4(30, -8, -7, 44),
        Vec4(-12, -8, 33, -6),
        Vec4(-41, -8, -7, -102),
        Vec4(-1, 6, -7, -13)));

    assert(m1 + m1 == Mat4(
        Vec4(-2, 6, -8, 12),
        Vec4(22, 6, 8, 10),
        Vec4(2, -6, 8, 174),
        Vec4(-6, -6, 8, -18)));

    assert(m2 - m2 == Mat4(
        Vec4(0, 0, 0, 0),
        Vec4(0, 0, 0, 0),
        Vec4(0, 0, 0, 0),
        Vec4(0, 0, 0, 0)));

    assert(m2 * -1 == Mat4(
        Vec4(-41, -3, -4, -55),
        Vec4(1, -3, -44, -5),
        Vec4(30, -3, -4, 91),
        Vec4(-10, -17, -4, 2)));

    assert(m1 * v2 == Vec4(429, 183, 129, -447));

    assert(m1 * m1 == Mat4(
        Vec4(12, 0, 24, -393),
        Vec4(11, 15, 4, 384),
        Vec4(-291, -279, 348, -444),
        Vec4(1, -3, -20, 396)));
    
    assert(m1 * m2 == Mat4(
        Vec4(136, 96, 136, 312),
        Vec4(378, 139, 212, 246),
        Vec4(794, 1485, 236, -498),
        Vec4(-330, -159, -164, -526)));
    
    assert(m2 * m1 == Mat4(
        Vec4(-169, -45, 84, 114),
        Vec4(63, -141, 212, 3792),
        Vec4(340, 180, -216, 1002),
        Vec4(187, 75, 36, 511)));
}