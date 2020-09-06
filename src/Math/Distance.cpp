#include "Math/Distance.hpp"

#include "Math/Point.hpp"
#include "Math/Vector.hpp"

float Distance::signedDstToCircle(Point_2d p, Point_2d centre, float radius)
{
    return ((Vector_2d)(centre - p)).length() - radius;
}

float Distance::signedDstToBox(Point_2d p, Point_2d centre, Vector_2d size)
{
    Vector_2d offset = ((Vector_2d)(p - centre)).abs() - size;

    float unsignedDst = offset.max(0).length();
    float dstInsideBox = offset.min(0).length();

    return unsignedDst + dstInsideBox;
}