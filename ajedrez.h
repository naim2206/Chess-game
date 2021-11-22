#ifndef AJEFREZ_H
#define AJEDREZ_H

#define SCREAN_HEIGHT 400
#define SCREAN_WIDTH 400
#define REC_SIZE 50

#include "raylib.h"

typedef struct player
{
    int whereToMoveX;
    int whereToMoveY;
    int whatToMoveX;
    int whatToMoveY;
    int primeraVezPeones[2][8];
} Player;

typedef struct game
{
    // -1 negro, 1 blanco
    int turn;
    int band;
} Game;

typedef struct piece
{
    int id;
} Piece;


typedef struct mytextures
{
    Texture2D texturepn;
    Texture2D texturepb;
    Texture2D texturean;
    Texture2D textureab;
    Texture2D texturecn;
    Texture2D texturecb;
    Texture2D texturetn;
    Texture2D texturetb;
    Texture2D texturedn;
    Texture2D texturedb;
    Texture2D texturern;
    Texture2D texturerb;
} myTexture;

void drawBoard(int board[8][8]);

Player* newPlayer();

void makeMove(Game* g, Player* p, int board_pieces[8][8]);

Game* newGame();

myTexture* loadTextures();

void drawPieces(int board[8][8], myTexture* t);

int checkWin(int board[8][8]);

void showWinner(int whoWon);


#endif
