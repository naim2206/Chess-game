#include "ajedrez.h"
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


int whatMove(Player* p, int board[8][8])
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (board[GetMouseY() / REC_SIZE][GetMouseX() / REC_SIZE] != 0)
        {
            p->whatToMoveX = GetMouseX() / REC_SIZE;
            p->whatToMoveY = GetMouseY() / REC_SIZE;
            return 1;
        }
    }
    return 0;

}

int whereMove(Player* p)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        p->whereToMoveX = GetMouseX() / REC_SIZE;
        p->whereToMoveY = GetMouseY() / REC_SIZE;
        return 2;
    }
    return 1;

}



Player* newPlayer()
{
    Player* p = malloc(sizeof(Player));
    p->whereToMoveX = 9;
    p->whereToMoveY = 9;
    p->whatToMoveX = 9;
    p->whatToMoveY = 9;
    return p;
}

Game* newGame()
{
    Game* g = malloc(sizeof(Game));
    g->turn = 1;
    return g;
}


int revisarMovPeonBlanco(int board[8][8], Player* p, int what)
{
    if (p->whatToMoveX == p->whereToMoveX)
    {
        if (p->whatToMoveY - p->whereToMoveY < 2 && p->whatToMoveY - p->whereToMoveY > 0)
        {
            return 1;
        }
    }
    return 0;
}

int revisarMovPeonNegro(int board[8][8], Player* p, int what)
{
    if (p->whatToMoveX == p->whereToMoveX)
    {
        if (p->whereToMoveY - p->whatToMoveY < 2 && p->whatToMoveY - p->whereToMoveY < 0)
        {
            return 1;
        }
    }
    return 0;
}

int revisarMovAlfil(int board[8][8], Player* p, int what)
{
    int diffMovY = p->whereToMoveY - p->whatToMoveY;
    int diffMovX = p->whereToMoveX - p->whatToMoveX;
    diffMovY = diffMovY > 0 ? diffMovY : -diffMovY;
    diffMovX = diffMovX > 0 ? diffMovX : -diffMovX;

    if (diffMovY == diffMovX)
    {
        return 1;
    }
    return 0;
}

int revisarMovTorre(int board[8][8], Player* p, int what)
{
    if (p->whatToMoveX == p->whereToMoveX || p->whatToMoveY == p->whereToMoveY)
    {
        return 1;
    }
    return 0;
}

int possibleMovePerPiece(int board[8][8], Player* p, int what)
{
    switch (what)
    {
    case 1: return revisarMovPeonBlanco(board, p, what);
    case -1: return revisarMovPeonNegro(board, p, what);
    case 2: return revisarMovAlfil(board, p, what);
    case -2:return revisarMovAlfil(board, p, what);
    case 5: return revisarMovTorre(board, p, what);
    case -5: return revisarMovTorre(board, p, what);
    default: return 1; // por ahora
    }
}

int changePeaces(int board[8][8], Player* p)
{
    int where = board[p->whereToMoveY][p->whereToMoveX];
    int what = board[p->whatToMoveY][p->whatToMoveX];

    // tambien falta nothingInMyWay();
    if (possibleMovePerPiece(board, p, what) == 1)
    {
        // los peones son super hdp 100% confirmado
        if (where == 0)
        {
            //mover pieza
            int temp;
            temp = what;
            board[p->whatToMoveY][p->whatToMoveX] = where;
            board[p->whereToMoveY][p->whereToMoveX] = temp;
            return 0;
        }
        // para que no te puedas suicidar
        if ((where > 0 && what < 0) || (where < 0 && what > 0))
        {
            // matar enemigo
            board[p->whereToMoveY][p->whereToMoveX] = what;
            board[p->whatToMoveY][p->whatToMoveX] = 0;
            return 1;
        }
        // vas contra tu equipo! cambia where
        return 1;
    }
    return 0;
}

void makeMove(int* band, Player* p, int board_pieces[8][8])
{
    if (*band == 0)
        *band = whatMove(p, board_pieces);
    else if (*band == 1)
        *band = whereMove(p);
    else if (*band == 2)
        *band = changePeaces(board_pieces, p);
}