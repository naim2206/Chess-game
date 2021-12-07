# proyecto_ajedrez
Juego de ajedrez como proyecto final de la materia Programación con memoria dinámica.
Implementado en C, utilizando la librería Raylib para las interfaces gráficas.

### Requisitos
tener [raylib](https://www.raylib.com) y un compilador de C instalado.
[wiki de raylib](https://github.com/raysan5/raylib/wiki/)

Su uso se ha probado para correr en vscode y en clion. 
Para usarlo en vscode se tiene que seguir [este tutorial](https://github.com/raysan5/raylib/wiki/Using-raylib-in-VSCode/), en la línea 361 del Makefile escribir <OBJS2 ?= ajedrez.c> y cambiar las líneas 378 y 379 por <$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME)$(EXT) $(OBJS) $(OBJS2) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)>. Se corre utilizando el debugger.
  
Su uso en macOS y Linux no ha sido probado.
