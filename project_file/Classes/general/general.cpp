#include"general.h"
void unitizeVec(Point* pot) 
{
    float length = sqrt(pot->x * pot->x + pot->y * pot->y);
    pot->x /= length;
    pot->y /= length;
}
