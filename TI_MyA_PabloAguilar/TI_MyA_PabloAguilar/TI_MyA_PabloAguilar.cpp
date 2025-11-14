#include <iostream>
#include "raylib.h"
#include "Personaje.h"
#include <vector>

const int x = 800;
const int y = 600;

float ancho = 40, alto = 10;

int main()
{
    InitWindow(x, y, "Meat_Exit");
    InitAudioDevice();
    SetTargetFPS(60);

    Personaje pie("assets/img/p_stand.png",x,y);

    std::vector<Rectangle> plataformas = {
        {x / 3.0f, y - 50, ancho, alto},
        {x / 2.0f, y - 100,ancho,alto},
        {x - 10.0f,y - 50,ancho,alto}
    };

    while (!WindowShouldClose()) {
       
        pie.Salto(plataformas);
        pie.Der();
        pie.Izq();

        BeginDrawing();
        ClearBackground(GRAY);
        
        for (auto& p : plataformas) {
            DrawRectangleRec(p, RED);
        }

        pie.Draw(); 
 
        EndDrawing();
    }
    pie.Unload();
    CloseWindow();

    return 0;
}

