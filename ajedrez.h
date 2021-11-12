#ifndef AJEFREZ_H
#define AJEDREZ_H

#define SCREAN_HEIGHT 500
#define ACCELERATION 1
#define NUM_OF_CIRCLES 5

struct circle
{
    float radius;
    int color;
    int x;
    int y;
    int speed;
};

void initCircle(struct circle* c, int x, int y);

void updateCircleState(struct circle* c);

#endif
