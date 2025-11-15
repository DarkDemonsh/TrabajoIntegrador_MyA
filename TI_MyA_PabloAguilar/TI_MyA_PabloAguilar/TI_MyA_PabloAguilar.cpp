#include <iostream>
#include "raylib.h"
#include "Personaje.h"
#include "Enemigo.h"
#include "global.h"
#include <vector>

const int x = 700;
const int y = 800;

float xg = 700;
float yg = 800;

float ancho = 40, alto = 10;

bool cerrar = false;
bool jugar = false;

int main()
{
    InitWindow(x, y, "Meat_Exit");
    InitAudioDevice();
    SetTargetFPS(60);

    Personaje jugador("assets/img/p_stand.png", x, y);
    Enemigo enemi("assets/img/e1.png", x, y, 0, 50); //El ultimo controla la velocidad

    std::vector<Rectangle> plataformas = {
        {x - 550, y - 100, ancho, alto},
        {x - 550, y - 200,ancho,alto},
        {x - 500, y - 300,ancho,alto},
        {x - 300, y - 250,ancho,alto},
        {x - 400, y - 350,ancho,alto},
        {x - 500, y -400,ancho,alto},
        {x - 400, y - 500,ancho,alto},
        {x - 300, y -600,ancho,alto},
        {x - 200, y -700,ancho,alto},
        {x - 100,y - 50,ancho,alto}
    };

    while (!WindowShouldClose()) {

        if (jugador.Ganar() && vida >= 1) {

            float recX1 = 200, recY1 = 100;

                Rectangle rec11 = {xg / 2.5, yg / 4.0, recX1, recY1};
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mouse1 = GetMousePosition();
                    if (CheckCollisionPointRec(mouse1, rec11)) {
                        win = true;
                        jugar = true;
                    }
                }
                Rectangle rec12 = { xg / 2.5, yg / 1.5, recX1, recY1 };
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mouse1 = GetMousePosition();
                    if (CheckCollisionPointRec(mouse1, rec12)) {
                        cerrar = true;
                    }
                }
                
                BeginDrawing();
                ClearBackground(BLACK);

                DrawText("GANASTE", xg / 2.3, yg / 2.0, 50, GREEN);

                DrawRectangle(xg / 2.5, yg / 4.0, 200, 100, GREEN);
                DrawText("Jugar", xg / 2.3, yg / 3.5, 50, WHITE);

                DrawRectangle(xg / 2.5, yg / 1.5, 200, 100, RED);
                DrawText("Salir", xg / 2.2, yg / 1.4, 50, WHITE);

                EndDrawing();
                if (cerrar) {
                    CloseWindow();
                }
        }
        
        if (vida <= 0) {

            float recX1 = 200, recY1 = 100;

            Rectangle rec11 = { xg / 2.5, yg / 4.0, recX1, recY1 };
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse1 = GetMousePosition();
                if (CheckCollisionPointRec(mouse1, rec11)) {
                    vida = 3;
                    jugar = true;
                }
            }
            Rectangle rec12 = { xg / 2.5, yg / 1.5, recX1, recY1 };
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse1 = GetMousePosition();
                if (CheckCollisionPointRec(mouse1, rec12)) {
                    cerrar = true;
                }
            }

            BeginDrawing();
            ClearBackground(BLACK);

            DrawText("PERDISTE", xg / 2.3, yg / 2.0, 50, RED);

            DrawRectangle(xg / 2.5, yg / 4.0, 200, 100, GREEN);
            DrawText("Jugar", xg / 2.3, yg / 3.5, 50, WHITE);

            DrawRectangle(xg / 2.5, yg / 1.5, 200, 100, RED);
            DrawText("Salir", xg / 2.2, yg / 1.4, 50, WHITE);

            EndDrawing();
            if (cerrar) {
                CloseWindow();
            }
        }

        if(!jugar && !jugador.Ganar() && vida >= 1){
            float recX = 200, recY = 100;
            Rectangle rec = { xg/2.5, yg / 4, recX, recY };
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mouse = GetMousePosition();
                    if (CheckCollisionPointRec(mouse, rec)) {
                        jugar = true;
                    }
                }
                Rectangle rec1 = { xg / 2.5, yg / 1.5, recX, recY };
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mouse = GetMousePosition();
                    if (CheckCollisionPointRec(mouse, rec1)) {
                        cerrar = true;
                    }
                }

                BeginDrawing();
                ClearBackground(BLACK);

                DrawRectangle(xg / 2.5, yg / 4, 200, 100, GREEN);
                DrawText("Jugar", xg / 2.3, yg / 3.5, 50, WHITE);

                DrawRectangle(xg / 2.5, yg / 1.5, 200, 100, RED);
                DrawText("Salir", xg / 2.2, yg / 1.4, 50, WHITE);
                
                EndDrawing();
                if (cerrar) {
                    CloseWindow();
                }
        }
        if (jugar && !jugador.Ganar() && vida >= 1) {
            win = false;
            jugador.Salto(plataformas);
            jugador.Der();
            jugador.Izq();
            
            enemi.MovEnemigo();
            enemi.EnemigoColision(jugador);

            BeginDrawing();
            ClearBackground(GRAY);
            DrawText(TextFormat("Vida: %d", vida),0,0, 50, WHITE);
            for (auto& p : plataformas) {
                DrawRectangleRec(p, RED);
            }
            enemi.Draw();
            jugador.Draw();

            EndDrawing();
        }
        
    }
    enemi.Unload();
    jugador.Unload();
    return 0;
}

