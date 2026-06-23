// Autor: Jose Marin
// Fecha: 2026-06-23
// Descripción: Representación de un grafo y varias de las operaciones que se pueden realizar sobre él.

#pragma once

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Nodo.h"
#include "Arco.h"
#include "Matrix.h"
#include "LinkedList.h"

using std::runtime_error;
using std::srand;
using std::rand;
using std::time;
using std::cout;
using std::endl;

class Grafo {
private:
	Matrix<int>* matrizAdyacencia; // representación en forma de matriz de adyacencia
	LinkedList<Arco>* listaAdyacencia; // representación en forma de lista de adyacencia, como un arreglo de listas
	int cantNodos; // número de nodos del grafo
	int maxArcosXNodo; // máximo número de arcos por nodo (para lista de adyacencia)
	int maxDistancia;  // longitud máxima de los arcos 
	int prob; // decidir aleatoriamente si los nodos están conectados o no, en base a cantNodos


public: 
	// Por cada celda, decidir aleatoriamente si los nodos están conectados (hay un arco) o no, si hay, asignar una distancia aleatoria (dentro del rango) al arco.
	Grafo() {
		this->cantNodos = 100;
		this->maxArcosXNodo = 6;
		this->maxDistancia = 200;
		this->prob = cantNodos / 10;
		if (prob < 1)
			prob = 1;
		
		matrizAdyacencia = new Matrix<int>(cantNodos, cantNodos);
		matrizAdyacencia->setAll(0);
		listaAdyacencia = new LinkedList<Arco>[cantNodos];

		srand(time(0));
		for (int i = 0; i < cantNodos; ++i) {
			for (int j = i + 1; j < cantNodos; ++j) {
				int r = rand() % prob;
				if (r == 0 && listaAdyacencia[i].getSize() < maxArcosXNodo && listaAdyacencia[j].getSize() < maxArcosXNodo) {
					int d = 1 + (rand() % maxDistancia);
					Arco a = Arco(i, j, d);
					matrizAdyacencia->setValue(i, j, d);
					matrizAdyacencia->setValue(j, i, d);
					listaAdyacencia[i].append(a);
					listaAdyacencia[j].append(a);
				}
			}
		}
	}
	// Libera la memoria de la matriz y la lista de adyacencia.
	~Grafo() {
		delete matrizAdyacencia;
		delete[] listaAdyacencia;
	}
};