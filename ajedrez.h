#ifndef AJEFREZ_H
#define AJEDREZ_H

#define SCREAN_HEIGHT 400
#define SCREAN_WIDTH 500
#define REC_SIZE 50
#define BOARD_WIDTH 400

#include "raylib.h"


// estructura con movimientos del jugador
typedef struct player Player;

// estructura con información de juego (hay que guardar)
typedef struct game Game;

// estructura con texturas de las imágenes por pieza
typedef struct mytextures myTexture;

typedef struct stack Stack;

// realiza la estructura del tablero (cuadros blancos y negros)
void drawBoard();

// datos iniciales a estrucura player
Player* newPlayer();

// permite seleccionar posiciones de movimiento y realizar movimiento
void makeMove(Game* g, Player* p, int board_pieces[8][8], Stack* s);
// datos iniciales a estructura game
Game* newGame();

// carga texturas a partir de imágenes de las piezas
myTexture* loadTextures();

// pone texturas de las piezas en su posición correspondiente según matriz de tablero
void drawPieces(int board[8][8], myTexture* t, Game* g, Player* p);

// revisa quien gana -1 negro, 1 blanco
int checkWin(int board[8][8]);

// muestra texto del jugador ganador
void showWinner(int whoWon);

// revisa si algún peon llegó a la última fila y lo corona a reina
void coronacion(int board[8][8]);

// dibuja botones de la derecha
void drawButtons();

// revisar si se presiona el boton de reiniciar juego
int startNewGame();

void checkSaveLoad(Game* g, int board[8][8], Stack* s);

// iluminar cuadro en el que está el mouse
void iluminar(int board[8][8]);

Stack* create(int board[8][8], Game* g);

int revisarUnJaqueChilo(int board[8][8]);

void drawJaque();

void makeMoveJaque(Game* g, Player* p, int board_pieces[8][8], Stack* s);

void freeVars(Game* g, Player* p, myTexture* t, Stack* s);

void inteliganciaArtificialChila(int board[8][8], Game* g, Player* p, Stack* s);


#endif
