#pragma once

struct Vector_2d;
struct Point_2d;

class Distance
{
public:
    static float signedDstToCircle(Point_2d p, Point_2d centre, float radius);
    static float signedDstToBox(Point_2d p, Point_2d centre, Vector_2d size);
};