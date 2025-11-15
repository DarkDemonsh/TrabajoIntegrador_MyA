#pragma once
#include "raylib.h"
#include "personaje.h"
#include <vector>

class Enemigo {
private:
	Texture2D textura;
	Vector2 pos;
	float scala;
	float v;
	float r;

public:

	Enemigo(const char* ruta, float x, float y, float v, float r);

	void Draw();
	void Unload();
	void MovEnemigo();
	void EnemigoColision(Personaje& p);

	Vector2 GetPos() const { return pos; }
	float GetScale() const { return scala; }
};