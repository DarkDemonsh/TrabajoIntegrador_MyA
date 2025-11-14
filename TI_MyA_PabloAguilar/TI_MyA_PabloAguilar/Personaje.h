#pragma once
#include "raylib.h"

class Personaje {
private:
	Texture2D textura;
	Vector2 pos;
	float scala;
	float salto1 = 0.0f;
	bool es_salto = false;
	const float g = 0.4f;
	const float s = -10.0f;
	float piso;

public:
	Personaje(const char* ruta, float x, float y);

	void Draw();
	void Unload();
	void Izq();
	void Der();
	void Salto();

	Vector2 GetPos() const { return pos; }
	float GetScale() const { return scala; }
};
