#ifndef AJEFREZ_H
#define AJEDREZ_H

#define SCREAN_HEIGHT 400
#define SCREAN_WIDTH 400
#define REC_SIZE 50

typedef struct player
{
    int whereToMoveX;
    int whereToMoveY;
    int whatToMoveX;
    int whatToMoveY;
    int turn;
} Player;


void drawBoard(int board[8][8]);

int makeMove(int board[8][8], Player* p);

int whatMove(Player* p, int board[8][8]);

int whereMove(Player* p);

Player* newPlayer();


#endif
