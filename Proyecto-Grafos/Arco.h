//Representa un arco (arista) de un grafo no dirigido
//Conecta dos nodos y almacena la distancia entre ellos.

class Arco {
private:
    int nodo1;
    int nodo2;
    int distancia;


public:
    // Constructor vacío
    Arco() {
        nodo1 = 0;
        nodo2 = 0;
        distancia = 0;
    }

public:

    Arco(int nodo1, int nodo2, int peso) {
        this->nodo1 = nodo1;
        this->nodo2 = nodo2;
        this->distancia = distancia;
    }

    int getNodo1() const {
        return nodo1;
    }

    int getNodo2() const {
        return nodo2;
    }

    int getPeso() const {
        return distancia;
    }

    void setNodo1(int nodo1) {
        this->nodo1 = nodo1;
    }

    void setNodo2(int nodo2) {
        this->nodo2 = nodo2;
    }

    void setPeso(int peso) {
        this->distancia = distancia;
    }
};