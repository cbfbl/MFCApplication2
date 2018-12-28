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
	return z;
}
