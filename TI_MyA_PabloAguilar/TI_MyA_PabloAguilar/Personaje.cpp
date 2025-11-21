#include <iostream>
#include "raylib.h"
#include "Personaje.h"
#include "global.h"
#include <vector>

Vector2 tpose;

int i = 1;

Personaje::Personaje(const char* ruta, float x, float y) {

	textura2 = LoadTexture("assets/img/p_Jump.png");

	textura = LoadTexture(ruta);

	cambio = textura;

	scala = fminf(50.0f / textura.width, 33.0f / textura.height);

	SetTextureFilter(textura, TEXTURE_FILTER_BILINEAR);

	pos = { (x / 2.0f) - (textura.width * scala / 2.0f),y - textura.height * scala  };
	tpose = pos;
	piso = y - textura.height * scala+20;

}

void Personaje::Draw() {
	if (hit) {
		pos = tpose;
		hit = false;
	}
	DrawRectangle(pos.x, pos.y,0.0f, textura.height,GREEN);
	DrawTextureEx(cambio, pos, 0.0f, scala, WHITE);
}

void Personaje::Unload() {
	UnloadTexture(textura);
	UnloadTexture(textura2);
}

void Personaje::Izq() {
	if (pos.x <= 2) {
		pos.x = 2;
	}else {
		if (IsKeyDown(KEY_A)) pos.x -= 4;
	}
}
void Personaje::Der() {
	if (pos.x >= 672) {
		pos.x = 672;
	}else {
		if (IsKeyDown(KEY_D)) pos.x += 4;
	}
}

void Personaje::Salto(const std::vector<Rectangle>& plataformas) {

	if (IsKeyPressed(KEY_SPACE) && !es_salto) {
		es_salto = true;
		salto1 = s;
		cambio = textura2;
	}

	if (i == 1 && !es_salto) {
		es_salto = true;
		i = 0;
	}
	if (es_salto && i == 0) {
		salto1 += g;
		pos.y += salto1;

	}
	if (es_salto && i == 1) {
	}



	Rectangle recPer = { pos.x, pos.y, textura.width * scala, textura.height * scala };

	for (const Rectangle& p : plataformas)

		if (CheckCollisionRecs(recPer, p) && salto1 > 0) {
			pos.y = p.y - recPer.height;
			es_salto = false;
			salto1 = 0;
			cambio = textura;

			bool caidaizq = recPer.width + recPer.x < p.x;
			bool caidader = recPer.x > p.width + p.width;

			if (caidaizq || caidader) {
				es_salto = true;
				salto1 = 0.1f;
				if (IsKeyPressed(KEY_SPACE)) {
					es_salto = true;
					salto1 = s;
					cambio = textura2;
				}
			}
		}

	if (pos.y >= piso) {
		pos.y = piso;
		salto1 = 0;
		es_salto = false;
	}

	if (pos.y == piso) {
		pos = tpose;
		i = 1;
		vida = vida - 1;
	}
}
bool Personaje::Ganar() {
	if(win){
		pos = tpose;
		return false;
	}
	if (pos.y >= -1) {
		return false;
	}
	else {
		return true;
	}
	

}

void Personaje::PRest() {
	if (IsKeyPressed(KEY_R)) {
		pos = tpose;
		vida = 3;
	}
}
