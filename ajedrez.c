#include "ajedrez.h"
#include <stdio.h>
#include <stdlib.h>


void updateCircleState(struct circle* c)
{
    if (c->y > SCREAN_HEIGHT)
    {
        c->speed = c->speed * -1;
    }
    else
    {
        c->speed += ACCELERATION;
    }
    c->y += c->speed;
}

void initCircle(struct circle* c, int x, int y)
{
    c->radius = 30;
    c->x = x;
    c->y = y;
    c->speed = 0;
}