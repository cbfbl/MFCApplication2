#include "Edge.h"

Edge::Edge() {}

Edge::Edge(Vec4 start, Vec4 end)
    : start(start)
    , end(end)
{
}

Edge::~Edge()
{
}

BOOL Edge::operator<(const Edge& rhs) const
{
    return ymin() < rhs.ymin();
}

BOOL Edge::operator==(const Edge& rhs) const
{
    //const Edge* pLhs = this;
    //const Edge* pRhs = &rhs;
    //return pLhs == pRhs;
    return start == rhs.start && end == rhs.end;
}

int Edge::ymin() const
{
    return (int)min(start.y, end.y);
}

int Edge::ymax() const
{
    return (int)max(start.y, end.y);
}

double Edge::getZ(double x, double y)
{
	if (end.y == start.y)
	{
		return min(end.z, start.z);
	}
	double z = ((y - start.y) / (end.y - start.y))*(end.z - start.z) + start.z;
	/*
	double x1 = start.x;
	double x2 = end.x;
	double y1 = start.y;
	double y2 = end.y;
	double z1 = start.z;
	double z2 = end.z;
	double x_step = x1 - x2;
	double y_step = y1 - y2;
	double z_step = z1 - z2;
	double z = 0.0;
	if (x_step != 0) {
		z = z1 + z_step * (x - x1) / x_step;
	}
	else if (y_step != 0) {
		z = z1 + z_step * (y - y1) / y_step;
	}
	else {
		z = min(z1,z2);
	}*/
	return z;
}
