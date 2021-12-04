#ifndef AJEFREZ_H
#define AJEDREZ_H

#define SCREAN_HEIGHT 400
#define SCREAN_WIDTH 400
#define REC_SIZE 50

#include "raylib.h"

// estructura con movimientos del jugador
typedef struct player
{
    int whereToMoveX;
    int whereToMoveY;
    int whatToMoveX;
    int whatToMoveY;
} Player;

// estructura con información de juego (hay que guardar)
typedef struct game
{
    // -1 negro, 1 blanco
    int turn;
    int band;
    int primeraVezPeones[2][8];
    int primeraVezEnroque[2][3];
} Game;


// estructura con texturas de las imágenes por pieza
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

// realiza la estructura del tablero (cuadros blancos y negros)
void drawBoard();

// datos iniciales a estrucura player
Player* newPlayer();

// permite seleccionar posiciones de movimiento y realizar movimiento
void makeMove(Game* g, Player* p, int board_pieces[8][8]);

// datos iniciales a estructura game
Game* newGame();

// carga texturas a partir de imágenes de las piezas
myTexture* loadTextures();

// pone texturas de las piezas en su posición correspondiente según matriz de tablero
void drawPieces(int board[8][8], myTexture* t);

// revisa quien gana -1 negro, 1 blanco
int checkWin(int board[8][8]);

// muestra texto del jugador ganador
void showWinner(int whoWon);

// revisa si algún peon llegó a la última fila y lo corona a reina
void coronacion(int board[8][8]);

#endif
