#include "ajedrez.h"
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"


void drawPiece(int i, int j, int board[8][8])
{
    Image* image = malloc(sizeof(Image));
    image = NULL;
    printf("%d\n", board[i][j]);
    switch (board[i][j])
    {
    case 1: *image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 2: *image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 3:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 5:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 9:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 10:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 20:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 30:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 50:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 90:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 100:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco
    case 1000:*image = LoadImage("pieces/Chess_plt60.png"); break; //peon blanco

    }
    if (image != NULL)
    {
        ImageDrawRectangle(image, i, j, REC_SIZE, REC_SIZE, RAYWHITE);
    }
}


void drawBoard(int board[8][8])
{
    ClearBackground(RAYWHITE);
    for (int i = 1; i < SCREAN_WIDTH / REC_SIZE; i += 2)
    {
        for (int j = 0; j < SCREAN_HEIGHT / REC_SIZE; j += 2)
        {
            DrawRectangle(i * REC_SIZE, j * REC_SIZE, REC_SIZE, REC_SIZE, BLACK);
            //drawPiece(i, j, board);
        }
    }
    for (int i = 0; i < SCREAN_WIDTH / REC_SIZE; i += 2)
    {
        for (int j = 1; j < SCREAN_HEIGHT / REC_SIZE; j += 2)
        {
            DrawRectangle(i * REC_SIZE, j * REC_SIZE, REC_SIZE, REC_SIZE, BLACK);
            //drawPiece(i, j, board);
        }
    }
}
