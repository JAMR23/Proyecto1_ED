// Un nodo del grafo con identificador y posición
#pragma once

class Nodo {
private: 
	int id;		//identificador
	float x;
	float y;

public:
	Nodo(int id, float x, float y) {
		this->id = id;
		this->x = x;
		this->y = y;
	}

	int getId() {
		return id;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float setX(float x) {
		this->x = x;
	}

	float setY(float y) {
		this->y = y;
	}
};

