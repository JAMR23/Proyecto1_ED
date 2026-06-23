//Interfaz con SFML para visualizar los algoritmos

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Grafo.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

//llena arreglos x, y con aleatorios
void generarPosiciones(float* x, float* y, int n) {
    srand((unsigned)time(0));
    int margen = 40;
    for (int i = 0; i < n; i++) {
        x[i] = margen + rand() % (1200 - margen * 2);
        y[i] = margen + rand() % (800 - margen * 2);
    }
}

void dibujarArcos(sf::RenderWindow& ventana, Grafo* g, float* x, float* y, int n, sf::Color color) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (g->getMatriz()->getValue(i, j) > 0) {
                sf::Vertex linea[2] = {
                    sf::Vertex(sf::Vector2f(x[i], y[i]), color),
                    sf::Vertex(sf::Vector2f(x[j], y[j]), color)
                };
                ventana.draw(linea, 2, sf::Lines);
            }
        }
    }
}

void dibujarNodos(sf::RenderWindow& ventana, float* x, float* y, int n, sf::Font& fuente) {
    for (int i = 0; i < n; i++) {
        sf::CircleShape
            c(10.f);
        c.setOrigin(10.f, 10.f);
        c.setPosition(x[i], y[i]);
        c.setFillColor(sf::Color(100, 180, 255));
        ventana.draw(c);

        sf::Text t;
        t.setFont(fuente);
        t.setString(std::to_string(i));
        t.setCharacterSize(9);
        t.setFillColor(sf::Color::Black);
        sf::FloatRect b = t.getLocalBounds();
        t.setOrigin(b.width / 2, b.height / 2);
        t.setPosition(x[i], y[i] - 2);
        ventana.draw(t);
    }
}

int main() {
    Grafo* grafo = new Grafo();
    int n = grafo->getCantNodos();

    float* x = new float[n];
    float* y = new float[n];
    generarPosiciones(x, y, n);

    cout << "----- Visualizador de Grafos -----" << endl;
    cout << "1. Ver grafo completo" << endl;
    cout << "2. DFS (arbol de expansion)" << endl;
    cout << "3. BFS (arbol de expansion)" << endl;
    cout << "Elija una opcion: ";

    int opcion = 1;
    cin >> opcion;

    int nodoInicial = 0;
    Grafo* arbol = nullptr;
    string titulo = "Grafo completo";

    if (opcion == 2 || opcion == 3) {
        cout << "Ingrese el nodo inicial (0 a " << n - 1 << "): ";
        cin >> nodoInicial;
        if (nodoInicial < 0 || nodoInicial >= n) nodoInicial = 0;

        if (opcion == 2) {
            arbol = grafo->DFS(nodoInicial);
            titulo = "DFS desde nodo " + to_string(nodoInicial);
        }
        else {
            arbol = grafo->BFS(nodoInicial);
            titulo = "BFS desde nodo " + to_string(nodoInicial);
        }
    }

    sf::RenderWindow ventana(sf::VideoMode(1200, 800), titulo, sf::Style::Close);
    ventana.setFramerateLimit(60);

    sf::Font fuente;
    if (!fuente.loadFromFile("arial.ttf"))
        fuente.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    sf::Text textoTitulo;
    textoTitulo.setFont(fuente);
    textoTitulo.setString(titulo);
    textoTitulo.setCharacterSize(18);
    textoTitulo.setFillColor(sf::Color(200, 200, 200));
    textoTitulo.setPosition(10, 10);

    while (ventana.isOpen()) {
        sf::Event ev;
        while (ventana.pollEvent(ev))
            if (ev.type == sf::Event::Closed) ventana.close();

        ventana.clear(sf::Color(30, 30, 30));

        if (arbol)
            dibujarArcos(ventana, arbol, x, y, n, sf::Color(80, 200, 120));
        else
            dibujarArcos(ventana, grafo, x, y, n, sf::Color(80, 80, 80));

        //nodo inicial es amarillo
        if (opcion == 2 || opcion == 3) {
            sf::CircleShape dest(12.f);
            dest.setOrigin(12.f, 12.f);
            dest.setPosition(x[nodoInicial], y[nodoInicial]);
            dest.setFillColor(sf::Color(255, 220, 50));
            ventana.draw(dest);
        }

        dibujarNodos(ventana, x, y, n, fuente);
        ventana.draw(textoTitulo);
        ventana.display();
    }

    delete grafo;
    delete arbol;
    delete[] x;
    delete[] y;
    return 0;
}



