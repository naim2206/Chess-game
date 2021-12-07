#include "raylib.h"
#include "ajedrez.h"
#include <stdlib.h>

int main()
{
    // peon 1, alfil 2, caballo 3, torre 5, Dama 9, rey 100, nada 0, 
    //negativo si es negro;
    //que piezas estan en que lugar
    int board_pieces[8][8] =
    { {-5,-3,-2,-9,-100,-2,-3,-5},
    {-1,-1,-1,-1,-1,-1,-1,-1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {5,3,2,9,100,2,3,5} };

    InitWindow(SCREAN_WIDTH, SCREAN_HEIGHT, "Chess");

    SetTargetFPS(60);

    Player* p = newPlayer();
    Game* g = newGame();
    myTexture* t = loadTextures();
    Stack* s = create(board_pieces, g);
    int whoWon = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (whoWon == 0 && revisarUnJaqueChilo(board_pieces) == 0)
        {
            // nadie ha ganado y no hay jaque
            makeMove(g, p, board_pieces, s);
            inteliganciaArtificialChila(board_pieces, g, p, s);
        }

        if (startNewGame() == 1)
        {
            //reiniciar juego
            EndDrawing();
            CloseWindow();
            main();
            return 0;
        }

        checkSaveLoad(g, board_pieces, s);
        drawBoard();
        iluminar(board_pieces);
        drawButtons();
        drawPieces(board_pieces, t, g, p);
        coronacion(board_pieces);
        startNewGame();

        if (revisarUnJaqueChilo(board_pieces))
        {
            drawJaque();

            inteliganciaArtificialChila(board_pieces, g, p, s);
            makeMoveJaque(g, p, board_pieces, s);
        }
        whoWon = checkWin(board_pieces);
        if (whoWon != 0)
        {
            showWinner(whoWon);
        }
        EndDrawing();
    }
    CloseWindow();
    freeVars(g, p, t, s);

    return 0;

}