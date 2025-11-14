#include <iostream>
#include "raylib.h"
#include "Personaje.h"

const int x = 800;
const int y = 600;

int main()
{
    InitWindow(x, y, "Meat_Exit");
    InitAudioDevice();
    SetTargetFPS(60);

    Personaje pie("assets/img/p_stand.png",x,y);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        
        pie.Draw();
        pie.Der();
        pie.Izq();
        pie.Salto();
        
        EndDrawing();
    }
    pie.Unload();
    CloseWindow();

    return 0;
}

