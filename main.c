#include "raylib.h"
#include "ajedrez.h"
#include <stdlib.h>

// peon 1, alfil 2, caballo 3, torre 5, Dama 9, rey 100, nada 0, 
//negativo si es negro;
//que piezas estan en que lugar
int board_pieces[8][8] = {
    {-5,-3,-2,-9,-100,-2,-3,-5},
    {-1,-1,-1,-1,-1,-1,-1,-1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {5,3,2,9,100,2,3,5},
};


int main()
{
    InitWindow(SCREAN_WIDTH, SCREAN_HEIGHT, "Chess");

    SetTargetFPS(60);

    Player* p = newPlayer();
    Game* g = newGame();
    myTexture* t = loadTextures();
    int whoWon = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (whoWon == 0)
        {
            drawBoard(board_pieces);
            drawPieces(board_pieces, t);
        }
        //falta revisar lo de los turnos
        makeMove(g, p, board_pieces);

        // pa debuggear
        //char pr[10];
        //itoa(whoWon, pr, 10);
        //if ((IsMouseButtonDown(MOUSE_RIGHT_BUTTON)))
        //    DrawText(pr, 10, 10, 20, BLUE);
        // hasta aqui

        whoWon = checkWin(board_pieces);
        if (whoWon != 0)
            showWinner(whoWon);
        EndDrawing();
    }
    CloseWindow();

    return 0;

}