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

/* Interpolate z at (x,y) */
double Edge::getZ(double x, double y)
{
    double z;
    if (end.x == start.x) {
	    if (end.y == start.y) {
		    z = min(end.z, start.z);
        } else {
            z = ((y - start.y) / (end.y - start.y)) * (end.z - start.z) + start.z;
        }
	} else {
        z = ((x - start.x) / (end.x - start.x)) * (end.z - start.z) + start.z;
    }
	return z;
}

/* Interpolate color at (x,y) */
COLORREF Edge::getColor(double x, double y)
{
    int r, g, b;
    if (end.x == start.x) {
        if (end.y == start.y) {
            r = min(end.r, start.r);
            g = min(end.g, start.g);
            b = min(end.b, start.b);
        } else {
            double cy = ((y - start.y) / (end.y - start.y));
            r = cy * (end.r - start.r) + start.r;
            g = cy * (end.g - start.g) + start.g;
            b = cy * (end.b - start.b) + start.b;
        }
    } else {
        double cx = ((x - start.x) / (end.x - start.x));
        r = cx * (end.r - start.r) + start.r;
        g = cx * (end.g - start.g) + start.g;
        b = cx * (end.b - start.b) + start.b;
    }
    return RGB(r, g, b);
}

/* Interpolate Phong normal direction at (x,y) */
Vec4 Edge::getPhongNormal(double x, double y)
{
    double dirX, dirY, dirZ;
    if (end.x == start.x) {
        if (end.y == start.y) {
            double dirX = min(end.dirX, start.dirX);
            double dirY = min(end.dirY, start.dirY);
            double dirZ = min(end.dirZ, start.dirZ);
            
        } else {
            double cy = ((y - start.y) / (end.y - start.y));
            dirX = cy * (end.dirX - start.dirX) + start.dirX;
            dirY = cy * (end.dirY - start.dirY) + start.dirY;
            dirZ = cy * (end.dirZ - start.dirZ) + start.dirZ;
        }
    } else {
        double cx = ((x - start.x) / (end.x - start.x));
        dirX = cx * (end.dirX - start.dirX) + start.dirX;
        dirY = cx * (end.dirY - start.dirY) + start.dirY;
        dirZ = cx * (end.dirZ - start.dirZ) + start.dirZ;
    }
    Vec4 dir(dirX, dirY, dirZ, 1);
    return dir.normalize();
}
