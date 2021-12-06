#include "ajedrez.h"
#include <stdlib.h>
#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

struct player
{
    int whereToMoveX;
    int whereToMoveY;
    int whatToMoveX;
    int whatToMoveY;
};

struct game
{
    // -1 negro, 1 blanco
    int turn;
    int band;
    int primeraVezPeones[2][8];
    int primeraVezEnroque[2][3];
};


struct mytextures
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
};

struct stack
{
    struct node* top;
};


struct node
{
    int board[8][8];
    //Game* g;
    int turn;
    int band;
    int primeraVezPeones[2][8];
    int primeraVezEnroque[2][3];
    struct node* prior;
};
typedef struct node Node;


void push(Stack* stack, int board_p[8][8], Game* g)
{
    Node* node = malloc(sizeof(Node));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            node->board[i][j] = board_p[i][j];
        }
    }

    node->band = g->band;
    node->turn = g->turn;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            node->primeraVezPeones[i][j] = g->primeraVezPeones[i][j];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            node->primeraVezEnroque[i][j] = g->primeraVezEnroque[i][j];

    node->prior = stack->top;
    stack->top = node;

}

Stack* create(int board[8][8], Game* g)
{
    Stack* stack = malloc(sizeof(Stack));
    stack->top = NULL;
    push(stack, board, g);
    return stack;

}

void pop(Stack* stack)
{

    if (stack->top == NULL)
        return;

    Node* toPop = stack->top;
    stack->top = toPop->prior;
    free(toPop);

}


// carga texturas a partir de imágenes de las piezas
myTexture* loadTextures()
{
    myTexture* t = malloc(sizeof(myTexture));
    t->texturepb = LoadTexture("pieces/Chess_plt60.png");  //peon blanco
    t->textureab = LoadTexture("pieces/Chess_blt60.png");  //alfil blanco
    t->texturecb = LoadTexture("pieces/Chess_nlt60.png");  //caballo blanco
    t->texturetb = LoadTexture("pieces/Chess_rlt60.png");  //torre blanco
    t->texturedb = LoadTexture("pieces/Chess_qlt60.png");  //dama blanco
    t->texturepn = LoadTexture("pieces/Chess_pdt60.png");  //peon negro
    t->texturean = LoadTexture("pieces/Chess_bdt60.png");  //alfil negro
    t->texturecn = LoadTexture("pieces/Chess_ndt60.png");  //caballo negro
    t->texturetn = LoadTexture("pieces/Chess_rdt60.png");  //torre negro
    t->texturedn = LoadTexture("pieces/Chess_qdt60.png");  //dama negro
    t->texturerb = LoadTexture("pieces/Chess_klt60.png");  //rey blanco
    t->texturern = LoadTexture("pieces/Chess_kdt60.png");  //rey negro

    return t;
}


// pone texturas de las piezas en su posición correspondiente según matriz de tablero
void drawPieces(int board[8][8], myTexture* t, Game* g, Player* p)
{
    for (int j = 0; j < SCREAN_WIDTH / REC_SIZE; j++)
        for (int i = 0; i < SCREAN_HEIGHT / REC_SIZE; i++)
        {
            // dibuja todo menos la seleccionada
            if ((g->band != 1 && g->band != 2) || j != p->whatToMoveY || i != p->whatToMoveX)
            {
                switch (board[j][i])
                {
                case 1: DrawTexture(t->texturepb, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //peon blanco
                case 2: DrawTexture(t->textureab, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //alfil blanco
                case 3: DrawTexture(t->texturecb, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE);break; //caballo blanco
                case 5: DrawTexture(t->texturetb, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE);break; //torre blanco
                case 9: DrawTexture(t->texturedb, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //dama blanco
                case -1: DrawTexture(t->texturepn, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //peon negro
                case -2: DrawTexture(t->texturean, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //alfil negro
                case -3: DrawTexture(t->texturecn, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //caballo negro
                case -5: DrawTexture(t->texturetn, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //torre negro
                case -9: DrawTexture(t->texturedn, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //dama negro
                case 100: DrawTexture(t->texturerb, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE);break; //rey blanco
                case -100: DrawTexture(t->texturern, i * REC_SIZE - 5, j * REC_SIZE - 5, RAYWHITE); break; //rey negro
                }
            }
        }
    // la pieza que se está moviendo
    if (g->band == 1)
    {
        switch (board[p->whatToMoveY][p->whatToMoveX])
        {
        case 1: DrawTexture(t->texturepb, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //peon blanco
        case 2: DrawTexture(t->textureab, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //alfil blanco
        case 3: DrawTexture(t->texturecb, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE);break; //caballo blanco
        case 5: DrawTexture(t->texturetb, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE);break; //torre blanco
        case 9: DrawTexture(t->texturedb, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //dama blanco
        case -1: DrawTexture(t->texturepn, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //peon negro
        case -2: DrawTexture(t->texturean, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //alfil negro
        case -3: DrawTexture(t->texturecn, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //caballo negro
        case -5: DrawTexture(t->texturetn, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //torre negro
        case -9: DrawTexture(t->texturedn, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //dama negro
        case 100: DrawTexture(t->texturerb, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE);break; //rey blanco
        case -100: DrawTexture(t->texturern, GetMouseX() - 30, GetMouseY() - 30, RAYWHITE); break; //rey negro
        }
    }
}



// realiza la estructura del tablero (cuadros blancos y negros)
void drawBoard()
{
    //fondo blanco
    ClearBackground(RAYWHITE);
    //pone cuadros negros en columnas impares con filas pares
    for (int i = 1; i < BOARD_WIDTH / REC_SIZE; i += 2)
    {
        for (int j = 0; j < SCREAN_HEIGHT / REC_SIZE; j += 2)
        {
            DrawRectangle(i * REC_SIZE, j * REC_SIZE, REC_SIZE, REC_SIZE, DARKGRAY);
        }
    }
    // pone cuadros negros en columnas pares con filas impares
    for (int i = 0; i < BOARD_WIDTH / REC_SIZE; i += 2)
    {
        for (int j = 1; j < SCREAN_HEIGHT / REC_SIZE; j += 2)
        {
            DrawRectangle(i * REC_SIZE, j * REC_SIZE, REC_SIZE, REC_SIZE, DARKGRAY);
        }
    }

}

// iluminar cuadro en el que está el mouse
void iluminar(int board[8][8])
{
    for (int i = 0; i < BOARD_WIDTH / REC_SIZE; i++)
        for (int j = 0; j < SCREAN_HEIGHT / REC_SIZE; j++)
            if (GetMouseX() / REC_SIZE == i && GetMouseY() / REC_SIZE == j)
                if (board[j][i] != 0)
                    DrawRectangle(i * REC_SIZE, j * REC_SIZE, REC_SIZE, REC_SIZE, YELLOW);
}


// obtiene la posición en la matriz de tablero de la pieza que se quiere mover
int whatMove(Player* p, int board[8][8])
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // que no se esté seleccionando un cuadro vacío
        if (board[GetMouseY() / REC_SIZE][GetMouseX() / REC_SIZE] != 0)
        {
            // guardar datos en estructura player
            p->whatToMoveX = GetMouseX() / REC_SIZE;
            p->whatToMoveY = GetMouseY() / REC_SIZE;
            // pasar a seleccionar a donde se va a mover
            return 1;
        }
    }
    // seguir esperando la seleccion del usuario
    return 0;

}

// obtiene la posición en la matriz de tablero del lugar al que se va a mover la pieza
int whereMove(Player* p)
{
    if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
    {
        // guardar datos en estructura player
        p->whereToMoveX = GetMouseX() / REC_SIZE;
        p->whereToMoveY = GetMouseY() / REC_SIZE;
        // pasar a realizar el movimiento
        return 2;
    }
    // seguir esperando la selección del usuario
    return 1;

}


// datos iniciales a estrucura player
Player* newPlayer()
{
    Player* p = malloc(sizeof(Player));
    p->whereToMoveX = 9;
    p->whereToMoveY = 9;
    p->whatToMoveX = 9;
    p->whatToMoveY = 9;

    return p;
}


// datos iniciales a estructura game
Game* newGame()
{
    Game* g = malloc(sizeof(Game));
    g->turn = 1;
    g->band = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
            g->primeraVezPeones[i][j] = 1;
        for (int j = 0; j < 3; j++)
            g->primeraVezEnroque[i][j] = 1;
    }
    return g;
}

// regresa 1 si es posible mover el peon y 0 si no
int revisarMovPeonBlanco(int board[8][8], Player* p, Game* g)
{
    // se mueve a un lugar vacío
    if (board[p->whereToMoveY][p->whereToMoveX] == 0)
    {
        // se puede mover 1 hacia arriba
        int maxMove = 1;

        // es la primera vez que se mueve y no hay nada en frente
        if (g->primeraVezPeones[1][p->whatToMoveX] == 1 && board[p->whatToMoveY - 1][p->whatToMoveX] == 0 && p->whatToMoveY == 6)
        {
            // puede moverse 2 posiciones
            maxMove = 2;
        }

        // se va a mover a la misma fila y a un lugar vacío
        if (p->whatToMoveX == p->whereToMoveX && board[p->whereToMoveY][p->whereToMoveX] == 0)
        {
            // se mueve menos que el maximo y no se regresa
            if (p->whatToMoveY - p->whereToMoveY <= maxMove && (p->whatToMoveY - p->whereToMoveY > 0))
            {
                // ya no es la primera vez que se mueve
                if (p->whatToMoveY == 6)
                    g->primeraVezPeones[1][p->whatToMoveX] = 0;
                // se puede realizar el movimiento
                return 1;
            }
        }
    }

    // quiere ir a pieza negra, se mueve hacia adelante y hacia uno de los lados (cruzado)
    if (board[p->whereToMoveY][p->whereToMoveX] < 0 && p->whatToMoveY - p->whereToMoveY == 1 && ((p->whatToMoveX - p->whereToMoveX) == 1 ? (p->whatToMoveX - p->whereToMoveX) : (-(p->whatToMoveX - p->whereToMoveX)) == 1))
        // se puede realizar el movimiento y es un asesinato
        return 1;
    return 0;
}


// regresa 1 si es posible mover el peon y 0 si no
int revisarMovPeonNegro(int board[8][8], Player* p, Game* g)
{
    // se mueve a un lugar vacío
    if (board[p->whereToMoveY][p->whereToMoveX] == 0)
    {
        // se puede mover 1 hacia abajo
        int maxMove = -1;

        // es la primera vez que se mueve y no hay nada en frente
        if (g->primeraVezPeones[0][p->whatToMoveX] == 1 && board[p->whatToMoveY + 1][p->whatToMoveX] == 0 && p->whatToMoveY == 1)
        {
            // puede moverse 2 posiciones hacia abajo
            maxMove = -2;
        }

        // se va a mover a la misma fila y a un lugar vacío
        if (p->whatToMoveX == p->whereToMoveX && board[p->whereToMoveY][p->whereToMoveX] == 0)
        {
            // se mueve menos que el maximo y hacia abajo
            if (p->whatToMoveY - p->whereToMoveY >= maxMove && (p->whatToMoveY - p->whereToMoveY < 0))
            {
                if (p->whatToMoveY == 1)
                    // ya no es la primera vez que se mueve
                    g->primeraVezPeones[0][p->whatToMoveX] = 0;
                // se puede realizar el movimiento
                return 1;
            }
        }
    }
    // se quiere mover hacia donde hay una pieza blanca y es uno hacia abajo y hacia alguno de los lados (cruzado)
    if (board[p->whereToMoveY][p->whereToMoveX] > 0 && p->whatToMoveY - p->whereToMoveY == -1 && ((p->whatToMoveX - p->whereToMoveX) == 1 ? (p->whatToMoveX - p->whereToMoveX) : (-(p->whatToMoveX - p->whereToMoveX)) == 1))
        // se puede realizar el movimiento, es un asesinato
        return 1;
    return 0;
}


// regresa 1 si es posible mover la pieza y 0 si no
int revisarMovAlfil(int board[8][8], Player* p)
{
    // cambios en dirección x y y
    int diffMovY = p->whereToMoveY - p->whatToMoveY;
    int diffMovX = p->whereToMoveX - p->whatToMoveX;

    int initX = p->whatToMoveX, initY = p->whatToMoveY;
    int finX = p->whereToMoveX;

    // obtener dirección en x y ya del movimiento
    int dirX = diffMovX < 0 ? -1 : 1;
    int dirY = diffMovY < 0 ? -1 : 1;

    // valores absolutos a diferencias de movimiento
    diffMovY = diffMovY > 0 ? diffMovY : -diffMovY;
    diffMovX = diffMovX > 0 ? diffMovX : -diffMovX;

    // hay movimiento cruzado
    if (diffMovY == diffMovX)
    {
        // revisar que no hay nada en el camino
        while (initX != (finX - dirX))
        {
            // iterar a travez del camino que se va a tomar
            initX += dirX;
            initY += dirY;
            if (board[initY][initX] != 0)
            {
                // hay algo en el camino, no se puede realizar movimiento
                return 0;
            }
        }
        // no hay nada en el camino, se puede relizar el movimiento
        return 1;
    }
    // no hay mov. cruzado bro
    return 0;
}


// regresa 1 si es posible mover la pieza y 0 si no
int revisarMovTorre(int board[8][8], Player* p, Game* g)
{
    int colori = board[p->whatToMoveY][p->whatToMoveX] < 0 ? 1 : 0;
    int direccionj = p->whatToMoveX == 0 ? 0 : 2;
    int initX = p->whatToMoveX, initY = p->whatToMoveY;
    int finY = p->whereToMoveY, finX = p->whereToMoveX;

    // cambios de posición en x y y
    int diffMovY = p->whereToMoveY - p->whatToMoveY;
    int diffMovX = p->whereToMoveX - p->whatToMoveX;
    int dir = 1;
    // vas a una casilla correcta
    if ((colori == 0 && board[p->whereToMoveY][p->whereToMoveX] <= 0)
        || (colori == 1 && board[p->whereToMoveY][p->whereToMoveX] >= 0))
    {
        // hay movimiento hacia arriba o abajo
        if (diffMovX == 0)
        {
            // si el movimiento es hacia abajo cambiar dirección
            if (diffMovY < 0)
            {
                dir *= -1;
            }

            // revisar que no hay nada en el camino
            while ((finY - dir) != initY)
            {
                // iterar a lo largo del camino
                initY += dir;
                if (board[initY][initX] != 0)
                {
                    // hay algo en el camino, no se puede relizar el movimiento
                    return 0;
                }
            }
            if ((p->whatToMoveX == 0 || p->whatToMoveX == 7) && (p->whatToMoveY == 0 || p->whatToMoveY == 7))
                // ya no es primera vez
                g->primeraVezEnroque[colori][direccionj] = 0;
            // se puede realizar el movimiento
            return 1;
        }

        // movimiento hacia la derecha o izquierda
        if (diffMovY == 0)
        {
            // si es hacia la izquierda cambiar dirección
            if (diffMovX < 0)
            {
                dir *= -1;
            }

            // revisar que no hay nada en el camino
            while ((finX - dir) != initX)
            {
                // iterar a lo largo del camino
                initX += dir;
                if (board[initY][initX] != 0)
                {
                    // hay algo en el camino, no se puede relizar el movimiento
                    return 0;
                }
            }
            if ((p->whatToMoveX == 0 || p->whatToMoveX == 7) && (p->whatToMoveY == 0 || p->whatToMoveY == 7))
                // ya no es primera vez
                g->primeraVezEnroque[colori][direccionj] = 0;
            // camino libre, se puede relizar el movimiento
            return 1;
        }
        // el movimiento no es recto bro
        return 0;
    }
    return 0;
}


// regresa 1 si es posible mover la pieza y 0 si no
int revisarMovCaballo(Player* p)
{
    // obtener valor absoluto de movimiento en x y y
    int diffMovY = p->whereToMoveY - p->whatToMoveY;
    int diffMovX = p->whereToMoveX - p->whatToMoveX;
    diffMovY = diffMovY > 0 ? diffMovY : -diffMovY;
    diffMovX = diffMovX > 0 ? diffMovX : -diffMovX;

    // el movimiento es 1 en una dirección y 2 en la otra (en L)
    if ((diffMovX == 1 && diffMovY == 2) || (diffMovX == 2 && diffMovY == 1))
    {
        // es posible mover la pieza
        return 1;
    }
    // no se puede mover
    return 0;
}


// regresa 1 si es posible mover la pieza y 0 si no
int revisarMovRey(Player* p, Game* g, int board[8][8])
{
    int colori = board[p->whatToMoveY][p->whatToMoveX] < 0 ? 1 : 0;
    // obtener valores absolutos de cambios en el movimiento
    int diffMovY = p->whereToMoveY - p->whatToMoveY;
    int diffMovX = p->whereToMoveX - p->whatToMoveX;
    diffMovY = diffMovY > 0 ? diffMovY : -diffMovY;
    diffMovX = diffMovX > 0 ? diffMovX : -diffMovX;

    // se mueve a una casilla válida
    if ((colori == 1 && board[p->whereToMoveY][p->whereToMoveX] >= 0)
        || (colori == 0 && board[p->whereToMoveY][p->whereToMoveX] <= 0))
    {
        // se mueve solo 1 en x
        if (diffMovX == 1)
        {
            // se mueve maximo 1 en y
            if (diffMovY <= 1)
            {
                // ya no es la primera vez
                //if ((colori == 1 && board[0][4] == -100)
                 //   || (colori == 0 && board[7][4] == 100))
                g->primeraVezEnroque[colori][1] = 0;
                // se puede realizar el movimiento
                return 1;
            }
        }
        // se muve solo 1 en y
        if (diffMovY == 1)
        {
            // se mueve maximo 1 en x
            if (diffMovX <= 1)
            {
                //if ((colori == 1 && board[0][4] == -100)
                    //|| (colori == 0 && board[7][4] == 100))
                g->primeraVezEnroque[colori][1] = 0;
                // se puede realizar el movimiento
                return 1;
            }
        }

        // enroque
        if (diffMovX == 2 && diffMovY == 0)
        {
            //blanco
            if (colori == 0 && p->whatToMoveY == 7 && p->whatToMoveX == 4 && g->primeraVezEnroque[colori][1] == 1)
            {
                // derecha
                if (p->whereToMoveX == 6 && board[7][7] == 5 && g->primeraVezEnroque[colori][2] == 1)
                {
                    if (board[7][5] == 0 && board[7][6] == 0)
                    {
                        return 2;
                    }
                }
                // izquierda
                if (p->whereToMoveX == 2 && board[7][0] == 5 && g->primeraVezEnroque[colori][0] == 1)
                {
                    if (board[7][1] == 0 && board[7][2] == 0 && board[7][3] == 0)
                    {
                        return 2;
                    }
                }
            }
            //negro
            if (colori == 1 && p->whatToMoveY == 0 && p->whatToMoveX == 4 && g->primeraVezEnroque[colori][1] == 1)
            {
                // derecha
                if (p->whereToMoveX == 6 && board[0][7] == -5 && g->primeraVezEnroque[colori][2] == 1)
                {
                    if (board[0][5] == 0 && board[0][6] == 0)
                    {
                        return 2;
                    }
                }
                // izquierda
                if (p->whereToMoveX == 2 && board[0][0] == -5 && g->primeraVezEnroque[colori][0] == 1)
                {
                    if (board[0][1] == 0 && board[0][2] == 0 && board[0][3] == 0)
                    {
                        return 2;
                    }
                }
            }
        }

        // se esta moviendo demasiado la pieza, no se puede mover 
        return 0;
    }
    return 0;
}


// regresa 1 si es posible mover la pieza y 0 si no
int revisarMovDama(Player* p, int board[8][8])
{
    // obtener dirección y valores absolutos de diferencias de movimientos
    int diffMovY = p->whereToMoveY - p->whatToMoveY;
    int diffMovX = p->whereToMoveX - p->whatToMoveX;
    int initX = p->whatToMoveX, initY = p->whatToMoveY;
    int finX = p->whereToMoveX, finY = p->whereToMoveY;
    int dirX = diffMovX < 0 ? -1 : 1;
    int dirY = diffMovY < 0 ? -1 : 1;
    diffMovY = diffMovY > 0 ? diffMovY : -diffMovY;
    diffMovX = diffMovX > 0 ? diffMovX : -diffMovX;

    // se mueve horizontalmente
    if (diffMovY == 0)
    {
        // revisa que no haya nada en el camino
        while ((finX - dirX) != initX)
        {
            initX += dirX;
            if (board[initY][initX] != 0)
            {
                // hay algo, no se puede mover
                return 0;
            }
        }
        // se puede mover
        return 1;
    }

    // se mueve verticalmente
    if (diffMovX == 0)
    {
        // revisa que no haya nada en el camino
        while ((finY - dirY) != initY)
        {
            initY += dirY;
            if (board[initY][initX] != 0)
            {
                // hay algo, no se puede mover
                return 0;
            }
        }
        // se puede mover
        return 1;
    }

    // se mueve de forma curzada
    if (diffMovY == diffMovX)
    {
        // revisa que no haya nada en el camino
        while (initX != (finX - dirX))
        {
            initX += dirX;
            initY += dirY;
            if (board[initY][initX] != 0)
            {
                // hay algo, no se puede mover
                return 0;
            }
        }
        // se puede mover
        return 1;
    }
    // el movimiento sta muy raro, no se puede hacer
    return 0;
}

// dependiendo de la pieza seleccionada por el usuario, se revisa si puede realizarse el movimiento (1 si, 0 no)
int possibleMovePerPiece(int board[8][8], Player* p, int what, Game* g)
{
    switch (what)
    {
    case 1: return revisarMovPeonBlanco(board, p, g);
    case -1: return revisarMovPeonNegro(board, p, g);
    case 2: return revisarMovAlfil(board, p);
    case -2:return revisarMovAlfil(board, p);
    case 5: return revisarMovTorre(board, p, g);
    case -5: return revisarMovTorre(board, p, g);
    case 3: return revisarMovCaballo(p);
    case -3: return revisarMovCaballo(p);
    case 100: return revisarMovRey(p, g, board);
    case -100: return revisarMovRey(p, g, board);
    case 9: return revisarMovDama(p, board);
    case -9: return revisarMovDama(p, board);
    default: return 0;
    }
}

int changePeaces(int board[8][8], Player* p, Game* g, Stack* s)
{
    // que hay en donde se quiere mover
    int where = board[p->whereToMoveY][p->whereToMoveX];
    // que se va a mover
    int what = board[p->whatToMoveY][p->whatToMoveX];

    if ((what < 0 && g->turn == -1) || (what > 0 && g->turn == 1))
    {

        // el movimiento es valido
        if (possibleMovePerPiece(board, p, what, g) == 1)
        {
            if (where == 0)
            {
                //va a un lugar vacío, se intercambia
                int temp;
                temp = what;
                board[p->whatToMoveY][p->whatToMoveX] = where;
                board[p->whereToMoveY][p->whereToMoveX] = temp;
                g->turn *= -1;
                // guardar en stack
                push(s, board, g);
                // regresa a selección de pieza a mover
                return 0;
            }

            // para no vas contra tu propio equipo
            if ((where > 0 && what < 0) || (where < 0 && what > 0))
            {
                // matar enemigo
                board[p->whereToMoveY][p->whereToMoveX] = what;
                board[p->whatToMoveY][p->whatToMoveX] = 0;
                // regresa a selección de pieza a mover
                g->turn *= -1;
                // guardar en stack
                push(s, board, g);
                return 0;
            }

            // no se realiza el movimiento
            return 0;
        }
        if (possibleMovePerPiece(board, p, what, g) == 2)
        {
            // enroque
            // negro
            if (what < 0)
            {
                // derecha
                if (p->whereToMoveX == 6)
                {
                    board[0][4] = 0;
                    board[0][7] = 0;
                    board[0][5] = -5;
                    board[0][6] = -100;
                    g->turn *= -1;
                    // guardar en stack
                    push(s, board, g);
                }
                // izquierda
                if (p->whereToMoveX == 2)
                {
                    board[0][0] = 0;
                    board[0][4] = 0;
                    board[0][3] = -5;
                    board[0][2] = -100;
                    g->turn *= -1;
                    // guardar en stack
                    push(s, board, g);
                }
            }
            // blanco
            if (what > 0)
            {
                // derecha
                if (p->whereToMoveX == 6)
                {
                    board[7][4] = 0;
                    board[7][7] = 0;
                    board[7][5] = 5;
                    board[7][6] = 100;
                    g->turn *= -1;
                    // guardar en stack
                    push(s, board, g);
                }
                // izquierda
                if (p->whereToMoveX == 2)
                {
                    board[7][0] = 0;
                    board[7][4] = 0;
                    board[7][3] = 5;
                    board[7][2] = 100;
                    g->turn *= -1;
                    // guardar en stack
                    push(s, board, g);
                }
            }

        }
        // regresa a selección de pieza a move// regresa a selección de pieza a mover

        return 0;
    }
    return 0;
}



// muestra texto del jugador ganador
void showWinner(int whoWon)
{
    char text[11];

    // guardar texto correspondiente a ganador
    if (whoWon == 1)
    {
        char textw[11] = "White won!";
        strcpy(text, textw);
    }
    else
    {
        char textb[11] = "Black won!";
        strcpy(text, textb);
    }

    //mostrar fondo blanco y texto del ganador
    DrawRectangle(50, 120, 300, 150, WHITE);
    DrawText(text, 75, 175, 50, BLACK);
}

// revisa si algún peon llegó a la última fila y lo corona a reina
void coronacion(int board[8][8])
{
    // revisa filas
    for (int i = 0; i < 8; i++)
    {
        if (board[0][i] == 1)
            board[0][i] = 9;

        if (board[7][i] == -1)
            board[7][i] = -9;
    }
}

// dibuja botones de la derecha
void drawButtons()
{
    DrawRectangle(BOARD_WIDTH + 10, SCREAN_HEIGHT / 9, 80, SCREAN_HEIGHT / 9, DARKGRAY);
    DrawRectangle(BOARD_WIDTH + 10, 3 * SCREAN_HEIGHT / 9, 80, SCREAN_HEIGHT / 9, DARKGRAY);
    DrawRectangle(BOARD_WIDTH + 10, 5 * SCREAN_HEIGHT / 9, 80, SCREAN_HEIGHT / 9, DARKGRAY);
    DrawRectangle(BOARD_WIDTH + 10, 7 * SCREAN_HEIGHT / 9, 80, SCREAN_HEIGHT / 9, DARKGRAY);

    DrawLine(BOARD_WIDTH, 0, BOARD_WIDTH + 1, SCREAN_HEIGHT, BLACK);

    DrawText("New Game", BOARD_WIDTH + 15, SCREAN_HEIGHT / 9 + 10, 13, WHITE);
    DrawText("Save Game", BOARD_WIDTH + 15, 3 * SCREAN_HEIGHT / 9 + 10, 13, WHITE);
    DrawText("Load Game", BOARD_WIDTH + 15, 5 * SCREAN_HEIGHT / 9 + 10, 13, WHITE);
    DrawText("Undo", BOARD_WIDTH + 15, 7 * SCREAN_HEIGHT / 9 + 10, 13, WHITE);
}

// revisar si se presiona el boton de reiniciar juego
int startNewGame()
{
    int x = GetMouseX(), y = GetMouseY();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        if (x > BOARD_WIDTH + 10 && x < BOARD_WIDTH + 90 && y > SCREAN_HEIGHT / 9 && y < 2 * SCREAN_HEIGHT / 9)
        {
            return 1;
        }
    return 0;
}

void saveGame(Game* g, int board[8][8])
{
    FILE* f = fopen("loadedGame.txt", "wb");
    fwrite(g, sizeof(Game), 1, f);
    fwrite(board, sizeof(int) * 64, 1, f);
    fclose(f);
}

void loadGame(Game* g, int board[8][8], Stack* s)
{
    FILE* f = fopen("loadedGame.txt", "rb");
    fread(g, sizeof(Game), 1, f);
    fread(board, sizeof(int) * 64, 1, f);
    fclose(f);
    push(s, board, g);
}



void goBack(Game* g, int board[8][8], Stack* s)
{
    if (s->top->prior != NULL)
    {
        pop(s);

        if (s->top != NULL)
        {
            g->turn = s->top->turn;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 8; j++)
                    g->primeraVezPeones[i][j] = s->top->primeraVezPeones[i][j];

            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 3; j++)
                    g->primeraVezEnroque[i][j] = s->top->primeraVezEnroque[i][j];

            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    board[i][j] = s->top->board[i][j];
        }
    }
}

void checkSaveLoad(Game* g, int board[8][8], Stack* s)
{
    int x = GetMouseX(), y = GetMouseY();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (x > BOARD_WIDTH + 10 && x < BOARD_WIDTH + 90 && y > 3 * SCREAN_HEIGHT / 9 && y < 4 * SCREAN_HEIGHT / 9)
        {
            saveGame(g, board);
        }
        if (x > BOARD_WIDTH + 10 && x < BOARD_WIDTH + 90 && y > 5 * SCREAN_HEIGHT / 9 && y < 6 * SCREAN_HEIGHT / 9)
        {
            loadGame(g, board, s);
        }
        if (x > BOARD_WIDTH + 10 && x < BOARD_WIDTH + 90 && y > 7 * SCREAN_HEIGHT / 9 && y < 8 * SCREAN_HEIGHT / 9)
        {
            goBack(g, board, s);
            goBack(g, board, s);
        }
    }
}

int getWhiteKingi(int board[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == 100)
                return i;
    return 0;
}

int getWhiteKingj(int board[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == 100)
                return j;
    return 0;
}

int getBlackKingi(int board[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == -100)
                return i;
    return 0;
}

int getBlackKingj(int board[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == -100)
                return j;
    return 0;
}



int revisarJaqueNegro(int board[8][8], int in, int jn)
{
    int tempi, tempj;

    // arriba
    tempi = in + 1;
    while (board[tempi][jn] >= 0 && tempi < 8)
    {
        if (board[tempi][jn] == 5 || board[tempi][jn] == 9)
            return 1;
        else if (board[tempi][jn] != 0)
            break;
        tempi++;
    }
    // abajo
    tempi = in - 1;
    while (board[tempi][jn] >= 0 && tempi >= 0)
    {
        if (board[tempi][jn] == 5 || board[tempi][jn] == 9)
            return 1;
        else if (board[tempi][jn] != 0)
            break;
        tempi--;
    }
    // izquierda
    tempj = jn - 1;
    while (board[in][tempj] >= 0 && tempj >= 0)
    {
        if (board[in][tempj] == 5 || board[in][tempj] == 9)
            return 1;
        else if (board[in][tempj] != 0)
            break;
        tempj--;
    }
    // derecha
    tempj = jn + 1;
    while (board[in][tempj] >= 0 && tempj < 8)
    {
        if (board[in][tempj] == 5 || board[in][tempj] == 9)
            return 1;
        else if (board[in][tempj] != 0)
            break;
        tempj++;
    }
    // arriba/derecha
    tempj = jn + 1;
    tempi = in + 1;
    while (board[tempi][tempj] >= 0 && tempi < 8 && tempj < 8)
    {
        if (board[tempi][tempj] == 2 || board[tempi][tempj] == 9)
            return 1;
        else if (board[tempi][tempj] != 0)
            break;
        tempj++;
        tempi++;
    }
    // arrina/izquierda
    tempj = jn - 1;
    tempi = in + 1;
    while (board[tempi][tempj] >= 0 && tempi < 8 && tempj >= 0)
    {
        if (board[tempi][tempj] == 2 || board[tempi][tempj] == 9)
            return 1;
        else if (board[tempi][tempj] != 0)
            break;
        tempj--;
        tempi++;
    }
    // abajo/derecha
    tempj = jn + 1;
    tempi = in - 1;
    while (board[tempi][tempj] >= 0 && tempj < 8 && tempi >= 0)
    {
        if (board[tempi][tempj] == 2 || board[tempi][tempj] == 9)
            return 1;
        else if (board[tempi][tempj] != 0)
            break;
        tempj++;
        tempi--;
    }
    // abajo/izquierda
    tempj = jn - 1;
    tempi = in - 1;
    while (board[tempi][tempj] >= 0 && tempj >= 0 && tempj >= 0)
    {
        if (board[tempi][tempj] == 2 || board[tempi][tempj] == 9)
            return 1;
        else if (board[tempi][tempj] != 0)
            break;

        tempj--;
        tempi--;
    }
    // rey
    if (board[in + 1][jn] == 100 || board[in - 1][jn] == 100 || board[in + 1][jn + 1] == 100 || board[in + 1][jn - 1] == 100 || board[in - 1][jn - 1] == 100 || board[in - 1][jn + 1] == 100 || board[in][jn + 1] == 100 || board[in][jn - 1] == 100)
        return 1;

    // peon
    if (board[in + 1][jn + 1] == 1 || board[in + 1][jn - 1] == 1)
        return 1;
    // caballo
    if (board[in - 2][jn - 1] == 3 || board[in - 2][jn + 1] == 3 || board[in + 2][jn - 1] == 3 || board[in + 2][jn + 1] == 3 || board[in - 1][jn - 2] == 3 || board[in - 1][jn + 2] == 3 || board[in + 1][jn - 2] == 3 || board[in + 1][jn + 2] == 3)
        return 1;


    return 0;
}


int revisarJaqueBlanco(int board[8][8], int ib, int jb)
{
    int tempi, tempj;
    // arriba
    tempi = ib + 1;
    while (board[tempi][jb] <= 0 && tempi < 8)
    {
        if (board[tempi][jb] == -5 || board[tempi][jb] == -9)
            return 1;
        else if (board[tempi][jb] != 0)
            break;
        tempi++;
    }
    // abajo
    tempi = ib - 1;
    while (board[tempi][jb] <= 0 && tempi >= 0)
    {
        if (board[tempi][jb] == -5 || board[tempi][jb] == -9)
            return 1;
        else if (board[tempi][jb] != 0)
            break;
        tempi--;
    }
    // izquierda
    tempj = jb - 1;
    while (board[ib][tempj] <= 0 && tempj >= 0)
    {
        if (board[ib][tempj] == -5 || board[ib][tempj] == -9)
            return 1;
        else if (board[ib][tempj] != 0)
            break;
        tempj--;
    }
    // derecha
    tempj = jb + 1;
    while (board[ib][tempj] <= 0 && tempj < 8)
    {
        if (board[ib][tempj] == -5 || board[ib][tempj] == -9)
            return 1;
        else if (board[ib][tempj] != 0)
            break;
        tempj++;
    }
    // arriba/derecha
    tempj = jb + 1;
    tempi = ib + 1;
    while (board[tempi][tempj] <= 0 && tempi < 8 && tempj < 8)
    {
        if (board[tempi][tempj] == -2 || board[tempi][tempj] == -9)
            return 1;
        else if (board[tempi][tempj] != 0)
            break;
        tempj++;
        tempi++;
    }
    // arriba/izquierda
    tempj = jb - 1;
    tempi = ib + 1;
    while (board[tempi][tempj] <= 0 && tempi < 8 && tempj >= 0)
    {
        if (board[tempi][tempj] == -2 || board[tempi][tempj] == -9)
            return 1;
        else if (board[tempi][tempj] != 0)
            break;
        tempj--;
        tempi++;
    }
    // abajo/derecha
    tempj = jb + 1;
    tempi = ib - 1;
    while (board[tempi][tempj] <= 0 && tempj < 8 && tempi >= 0)
    {
        if (board[tempi][tempj] == -2 || board[tempi][tempj] == -9)
            return 1;
        else if (board[tempi][tempj] != 0)
            break;
        tempj++;
        tempi--;
    }
    // abajo/izquierda
    tempj = jb - 1;
    tempi = ib - 1;
    while (board[tempi][tempj] <= 0 && tempj >= 0 && tempj >= 0)
    {
        if (board[tempi][tempj] == -2 || board[tempi][tempj] == -9)
            return 1;
        else if (board[tempi][tempj] != 0)
            break;

        tempj--;
        tempi--;
    }
    // rey
    if (board[ib + 1][jb] == -100 || board[ib - 1][jb] == -100 || board[ib + 1][jb + 1] == -100 || board[ib + 1][jb - 1] == -100 || board[ib - 1][jb - 1] == -100 || board[ib - 1][jb + 1] == -100 || board[ib][jb + 1] == -100 || board[ib][jb - 1] == -100)
        return 1;

    // peon
    if (board[ib - 1][jb + 1] == -1 || board[ib - 1][jb - 1] == -1)
        return 1;
    // caballo
    if (board[ib - 2][jb - 1] == -3 || board[ib - 2][jb + 1] == -3 || board[ib + 2][jb - 1] == -3 || board[ib + 2][jb + 1] == -3 || board[ib - 1][jb - 2] == -3 || board[ib - 1][jb + 2] == -3 || board[ib + 1][jb - 2] == -3 || board[ib + 1][jb + 2] == -3)
        return 1;

    return 0;
}

int revisarUnJaqueChilo(int board[8][8])
{
    if (revisarJaqueBlanco(board, getWhiteKingi(board), getWhiteKingj(board)) == 1)
        return 1;
    if (revisarJaqueNegro(board, getBlackKingi(board), getBlackKingj(board)) == 1)
        return 1;
    return 0;
}


void drawJaque()
{
    DrawText("Jaque", 100, 175, 50, BLACK);
}

int revisarJaqueMateBlanco(int board[8][8])
{
    int ib = getWhiteKingi(board);
    int jb = getWhiteKingj(board);

    if (revisarJaqueBlanco(board, ib + 1, jb + 1) == 0 && board[ib + 1][jb + 1] <= 0 && jb + 1 < 8 && ib + 1 < 8)
        return 0;
    if (revisarJaqueBlanco(board, ib - 1, jb + 1) == 0 && board[ib - 1][jb + 1] < 0 && jb + 1 < 8 && ib - 1 >= 0)
        return 0;
    if (revisarJaqueBlanco(board, ib + 1, jb - 1) == 0 && board[ib + 1][jb - 1] < 0 && jb - 1 >= 0 && ib + 1 < 8)
        return 0;
    if (revisarJaqueBlanco(board, ib - 1, jb - 1) == 0 && board[ib - 1][jb - 1] < 0 && jb - 1 >= 0 && ib - 1 >= 0)
        return 0;
    if (revisarJaqueBlanco(board, ib, jb + 1) == 0 && board[ib][jb + 1] <= 0 && jb + 1 < 8)
        return 0;
    if (revisarJaqueBlanco(board, ib + 1, jb) == 0 && board[ib + 1][jb] <= 0 && ib + 1 < 8)
        return 0;
    if (revisarJaqueBlanco(board, ib, jb - 1) == 0 && board[ib][jb - 1] <= 0 && jb - 1 >= 0)
        return 0;
    if (revisarJaqueBlanco(board, ib - 1, jb) == 0 && board[ib - 1][jb] <= 0 && ib - 1 >= 0)
        return 0;

    return 1;
}

int revisarJaqueMateNegro(int board[8][8])
{
    int jn = getBlackKingj(board);
    int in = getBlackKingi(board);

    if (revisarJaqueNegro(board, in + 1, jn + 1) == 0 && board[in + 1][jn + 1] >= 0 && in + 1 < 8 && jn + 1 < 8)
        return 0;
    if (revisarJaqueNegro(board, in - 1, jn + 1) == 0 && board[in - 1][jn + 1] >= 0 && jn + 1 < 8 && in - 1 >= 0)
        return 0;
    if (revisarJaqueNegro(board, in + 1, jn - 1) == 0 && board[in + 1][jn - 1] >= 0 && in + 1 < 8 && jn - 1 >= 0)
        return 0;
    if (revisarJaqueNegro(board, in - 1, jn - 1) == 0 && board[in - 1][jn - 1] >= 0 && in - 1 >= 0 && jn - 1 >= 0)
        return 0;
    if (revisarJaqueNegro(board, in, jn + 1) == 0 && board[in][jn + 1] >= 0 && jn + 1 < 8)
        return 0;
    if (revisarJaqueNegro(board, in + 1, jn) == 0 && board[in + 1][jn] >= 0 && in + 1 < 88)
        return 0;
    if (revisarJaqueNegro(board, in, jn - 1) == 0 && board[in][jn - 1] >= 0 && jn - 1 >= 0)
        return 0;
    if (revisarJaqueNegro(board, in - 1, jn) == 0 && board[in - 1][jn] >= 0 && in - 1 >= 0)
        return 0;

    return 1;
}


// revisa quien gana -1 negro, 1 blanco, 0 nadie
int checkWin(int board[8][8])
{
    // cambiar a que sea cuando hay jaque mate
    int blackWin = -1;
    int whiteWin = 1;
    if (revisarJaqueMateBlanco(board) == 1)
        return blackWin;
    if (revisarJaqueMateNegro(board) == 1)
        return whiteWin;
    return 0;
}


void freeVars(Game* g, Player* p, myTexture* t, Stack* s)
{
    free(p);
    free(g);
    free(t);
    free(s);
}


int revisarAutoJaque(int board[8][8], Player* p, Game* g)
{
    if (g->turn == 1)
    {
        if (revisarJaqueNegro(board, getBlackKingi(board), getBlackKingj(board)) == 1)
        {
            return 1;
        }
    }
    if (g->turn == -1)
    {
        if (revisarJaqueBlanco(board, getWhiteKingi(board), getWhiteKingj(board)) == 1)
        {
            return 1;
        }
    }
    return 0;
}

// permite seleccionar posiciones de movimiento y realizar movimiento
void makeMove(Game* g, Player* p, int board_pieces[8][8], Stack* s)
{
    if (GetMouseX() < BOARD_WIDTH)
    {
        if (g->band == 0)
            // selección de pieza a mover
            g->band = whatMove(p, board_pieces);
    }
    if (g->band == 1)
        // selección de lugar a moverse
        g->band = whereMove(p);
    else if (g->band == 2)
    {
        // realizar movimiento
        g->band = changePeaces(board_pieces, p, g, s);

        if (revisarAutoJaque(board_pieces, p, g) == 1)
            goBack(g, board_pieces, s);
        g->band = 0;
    }

}


void makeMoveJaque(Game* g, Player* p, int board_pieces[8][8], Stack* s)
{
    /*if (GetMouseX() < BOARD_WIDTH)
    {
        if (g->band == 0)
            // selección de pieza a mover
            g->band = whatMove(p, board_pieces);
    }
    if (board_pieces[p->whatToMoveY][p->whatToMoveX] == 100 || board_pieces[p->whatToMoveY][p->whatToMoveX] == -100)
    {
        if (g->band == 1)
            // selección de lugar a moverse
            g->band = whereMove(p);
        else if (g->band == 2)
        {
            // realizar movimiento
            g->band = changePeaces(board_pieces, p, g, s);

            if (revisarAutoJaque(board_pieces, p, g) == 1)
                goBack(g, board_pieces, s);


            g->band = 0;
        }

    }
    else
    {
        g->band = 0;
    }*/

    makeMove(g, p, board_pieces, s);

    //if (revisarUnJaqueChilo(board_pieces) == 1)
    //    goBack(g, board_pieces, s);

}

void inteliganciaArtificialChila(int board[8][8], Game* g, Player* p, Stack* s)
{
    if (g->turn == -1)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 8; l++)
                    {
                        if (board[j][i] < 0)
                        {
                            p->whatToMoveX = i;
                            p->whatToMoveY = j;
                            p->whereToMoveX = k;
                            p->whereToMoveY = l;
                            if (board[p->whereToMoveY][p->whereToMoveX] > 0)
                            {
                                changePeaces(board, p, g, s);
                                //if (revisarAutoJaque(board, p, g) == 1)
                                //    goBack(g, board, s);
                                g->band = 0;
                            }
                        }

                    }

                }

            }

        }
    }

    srand(time(NULL));
    while (g->turn == -1)
    {
        p->whatToMoveX = rand() % 8;
        p->whatToMoveY = rand() % 8;
        p->whereToMoveX = rand() % 8;
        p->whereToMoveY = rand() % 8;
        changePeaces(board, p, g, s);
        if (revisarAutoJaque(board, p, g) == 1)
            goBack(g, board, s);
        g->band = 0;
    }

}
