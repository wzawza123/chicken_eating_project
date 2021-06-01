#include"general.h"
Point unitizeVec(Point& pot) 
{
    float length = sqrt(pot.x * pot.x + pot.y * pot.y);
    return pot / length;
}
