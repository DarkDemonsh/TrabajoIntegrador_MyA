#include <iostream>
#include "raylib.h"
#include "Personaje.h"
#include <vector>

Personaje::Personaje(const char* ruta, float x, float y) {

	textura = LoadTexture(ruta);

	scala = fminf(50.0f / textura.width, 33.0f / textura.height);

	SetTextureFilter(textura, TEXTURE_FILTER_BILINEAR);

	pos = { (x / 2.0f) - (textura.width * scala / 2.0f),y - textura.height * scala };
	piso = y - textura.height * scala;
}

void Personaje::Draw() {
	DrawRectangle(pos.x, pos.y,0.0f, textura.height,GREEN);
	DrawTextureEx(textura, pos, 0.0f, scala, WHITE);
}

void Personaje::Unload() {
	UnloadTexture(textura);
}

void Personaje::Izq() {
	if (pos.x <= 2) {
		pos.x = 2;
	}else {
		if (IsKeyDown(KEY_A)) pos.x -= 4;
	}
}
void Personaje::Der() {
	if (pos.x >= 772) {
		pos.x = 772;
	}else {
		if (IsKeyDown(KEY_D)) pos.x += 4;
	}
}

void Personaje::Salto(const std::vector<Rectangle>& plataformas) {

	if (IsKeyDown(KEY_W) && !es_salto) {
		es_salto = true;
		salto1 = s;
	}
	if (es_salto) {
		salto1 += g;
		pos.y += salto1;

	}
	Rectangle recPer = { pos.x, pos.y, textura.width * scala, textura.height * scala };

	for (const Rectangle& p : plataformas)

		if (CheckCollisionRecs(recPer, p) && salto1 > 0) {
			DrawText("Pulsa S para Agacharte", 0, 0, 20, WHITE);
			pos.y = p.y - recPer.height;
			es_salto = false;
			salto1 = 0;

			bool caidaizq = recPer.width + recPer.x < p.x;
			bool caidader = recPer.x > p.width + p.width;

			if (caidaizq || caidader) {
				es_salto = true;
				salto1 = 0.1f;
				if (IsKeyDown(KEY_W)) {
					es_salto = false;
				}
			}
		}

	if (pos.y >= piso) {
		pos.y = piso;
		salto1 = 0;
		es_salto = false;
	}
}
