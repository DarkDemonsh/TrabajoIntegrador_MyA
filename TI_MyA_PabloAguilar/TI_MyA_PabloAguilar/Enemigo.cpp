#include <iostream>
#include "raylib.h"
#include "Enemigo.h"
#include "Personaje.h"
#include "global.h"

Enemigo::Enemigo(const char* ruta, float x, float y, float r, float vlo) {

	textura = LoadTexture(ruta);

	scala = fminf(20.0f / textura.width, 20.0f / textura.height);

	SetTextureFilter(textura, TEXTURE_FILTER_BILINEAR);

	pos = { x - (textura.width * scala ) / 2.0f,(y/2) - (textura.height * scala)/2.0f };
	v = vlo;
}

void Enemigo::Draw() {
	Vector2 texpos = { pos.x - (textura.width * scala) / 2.0f,pos.y - (textura.height * scala) / 2.0f };
	DrawTextureEx(textura, texpos, 0.0f, scala, WHITE);
}

void Enemigo::Unload() {
	UnloadTexture(textura);
}

void Enemigo::MovEnemigo() {
	int x = 750;
	float dt = GetFrameTime();
	float limitizq = 0;
	float limitder = 750;

	pos.x += v * dt;

	if (pos.x >= limitder) {
		pos.x = limitder;
		pos.x = -v;
		r++;
	}
	else if (pos.x <= limitizq) {
		pos.x = limitizq;
		v = -v;
		r++;
	}
}

void Enemigo::EnemigoColision(Personaje& p) {
	float x = 700;
	float y = 800;
	Vector2 piso = { x - (textura.width * scala) / 2.0f,y - (textura.height * scala) / 2.0f }; 
	if(CheckCollisionCircles(pos, 10.f, p.GetPos(), 10.f)){
		vida = vida - 1;
		hit = true;
	}

}

void Enemigo::ERest() {
	if (IsKeyPressed(KEY_R)) {
		pos.x = 0;
	}
}