#include "raylib.h"
#include "ajedrez.h"
#include <stdlib.h>
#include <stdio.h>


int main()
{
    InitWindow(500, SCREAN_HEIGHT, "el repaso");
    SetTargetFPS(60);

    struct circle c[NUM_OF_CIRCLES];

    for (int i = 0; i < NUM_OF_CIRCLES; ++i)
        initCircle(c + i, 50 * i, 5 * i);

    while (!WindowShouldClose())
    {

        for (int i = 0; i < NUM_OF_CIRCLES; ++i)
            updateCircleState(c + i);


        BeginDrawing();
        {
            ClearBackground(WHITE);

            for (int i = 0; i < NUM_OF_CIRCLES; ++i)
                DrawCircle(c[i].x, c[i].y, c[i].radius, RED);


            DrawFPS(10, 10);

        }

        EndDrawing();



    }
}