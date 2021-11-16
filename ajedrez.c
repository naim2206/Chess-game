#include "ajedrez.h"
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

// revisa que pieza se debe colocar y la dibuja
void drawPiece(int i, int j, int board[8][8])
{
    Texture2D texture;
    int entra = 1;
    switch (board[j][i])
    {
    case 1: texture = LoadTexture("pieces/Chess_plt60.png"); break; //peon blanco
    case 2: texture = LoadTexture("pieces/Chess_blt60.png"); break; //alfil blanco
    case 3: texture = LoadTexture("pieces/Chess_nlt60.png"); break; //caballo blanco
    case 5: texture = LoadTexture("pieces/Chess_rlt60.png"); break; //torre blanco
    case 9: texture = LoadTexture("pieces/Chess_qlt60.png"); break; //dama blanco
    case -1: texture = LoadTexture("pieces/Chess_pdt60.png"); break; //peon negro
    case -2: texture = LoadTexture("pieces/Chess_bdt60.png"); break; //alfil negro
    case -3: texture = LoadTexture("pieces/Chess_ndt60.png"); break; //caballo negro
    case -5: texture = LoadTexture("pieces/Chess_rdt60.png"); break; //torre negro
    case -9: texture = LoadTexture("pieces/Chess_qdt60.png"); break; //dama negro
    case 100: texture = LoadTexture("pieces/Chess_klt60.png"); break; //rey blanco
    case -100: texture = LoadTexture("pieces/Chess_kdt60.png"); break; //rey negro
    default: entra = 0; // no debe dibujar nada
    }
    if (entra == 1)
    {
        DrawTexture(texture, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE);
    }
}

//mostrar tablero y piezas
void drawBoard(int board[8][8])
{
    //fondo blanco
    ClearBackground(RAYWHITE);
    //pone cuadros negros
    for (int i = 1; i < SCREAN_WIDTH / REC_SIZE; i += 2)
    {
        for (int j = 0; j < SCREAN_HEIGHT / REC_SIZE; j += 2)
        {
            DrawRectangle(i * REC_SIZE, j * REC_SIZE, REC_SIZE, REC_SIZE, DARKGRAY);
        }
    }
    for (int i = 0; i < SCREAN_WIDTH / REC_SIZE; i += 2)
    {
        for (int j = 1; j < SCREAN_HEIGHT / REC_SIZE; j += 2)
        {
            DrawRectangle(i * REC_SIZE, j * REC_SIZE, REC_SIZE, REC_SIZE, DARKGRAY);
        }
    }
    //coloca las piezas en su lugar
    for (int j = 0; j < SCREAN_WIDTH / REC_SIZE; j++)
        for (int i = 0; i < SCREAN_HEIGHT / REC_SIZE; i++)
        {
            drawPiece(i, j, board);
        }
}
