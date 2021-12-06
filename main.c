#include "raylib.h"
#include "ajedrez.h"
#include <stdlib.h>

/*
1, 1, 1 - blanco
1, 1, 1 - negro
*/

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
        inteliganciaArtificialChila(board_pieces, g, p, s);
        if (whoWon == 0 && revisarUnJaqueChilo(board_pieces) == 0)
            // nadie ha ganado y no hay jaque
            makeMove(g, p, board_pieces, s);

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


        // pa debuggear
        //char pr[10];
        //itoa(whoWon, pr, 10);
        //if ((IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)))
        //    DrawText(pr, 10, 10, 20, BLUE);
        // hasta aqui

        startNewGame();


        if (revisarUnJaqueChilo(board_pieces))
        {
            drawJaque();
            // mate?
            whoWon = checkWin(board_pieces);
            if (whoWon != 0)
            {
                showWinner(whoWon);
            }
            else
            {
                // solo mover el rey
                makeMoveJaque(g, p, board_pieces, s);
                // luego revisar que no se pueda poner en jaque a si mismo
                //tapar
            }
        }
        EndDrawing();
    }
    CloseWindow();
    freeVars(g, p, t, s);

    return 0;

}