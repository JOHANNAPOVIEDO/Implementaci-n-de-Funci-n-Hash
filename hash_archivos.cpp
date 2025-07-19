
#include <iostream>
using namespace std;

const int TAM_TABLA = 20;

struct Nodo {
    int clave;
    Nodo* sig;
};

Nodo* tablaHash[TAM_TABLA]; // tabla principal
int colisiones = 0;
int elementosEnColisiones = 0;

// Función hash
int FuncionHash(int clave, int tamanoTabla) {
    return clave % tamanoTabla;
}

// Insertar elemento
void InsertarElemento(int clave) {
    int pos = FuncionHash(clave, TAM_TABLA);
    Nodo* nuevo = new Nodo;
    nuevo->clave = clave;
    nuevo->sig = NULL;

    if (tablaHash[pos] == NULL) {
        tablaHash[pos] = nuevo;
    } else {
        colisiones++;
        elementosEnColisiones++;
        Nodo* temp = tablaHash[pos];
        while (temp->sig != NULL) temp = temp->sig;
        temp->sig = nuevo;
    }
}

// Mostrar ocupación
void MostrarOcupacion() {
    cout << "Tamaño del Área de Colisiones: " << TAM_TABLA << endl;
    cout << "Número de elementos en área de colisiones: " << elementosEnColisiones << endl;
    float porcentaje = (elementosEnColisiones * 100.0) / TAM_TABLA;
    cout << "Porcentaje de ocupación: " << porcentaje << "%" << endl;
}

// Mostrar tabla
void MostrarTabla() {
    for (int i = 0; i < TAM_TABLA; ++i) {
        cout << "[" << i << "]: ";
        Nodo* temp = tablaHash[i];
        while (temp != NULL) {
            cout << temp->clave << " -> ";
            temp = temp->sig;
        }
        cout << "NULL" << endl;
    }
}

int main() {
    for (int i = 0; i < TAM_TABLA; ++i) tablaHash[i] = NULL;

    int valores[20] = { 3, 18, 41, 26, 7, 14, 33, 12, 9, 28, 19, 8, 21, 5, 17, 22, 1, 36, 39, 2 };

    int opcion;
    do {
        cout << "\n1. Insertar un elemento manualmente";
        cout << "\n2. Mostrar ocupación";
        cout << "\n3. Mostrar tabla";
        cout << "\n4. Insertar automáticamente 20 elementos";
        cout << "\n5. Salir\nOpción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int clave;
                cout << "Ingrese clave: ";
                cin >> clave;
                InsertarElemento(clave);
                break;
            }
            case 2:
                MostrarOcupacion();
                break;
            case 3:
                MostrarTabla();
                break;
            case 4:
                for (int i = 0; i < 20; i++) {
                    InsertarElemento(valores[i]);
                }
                cout << "Se insertaron automáticamente 20 elementos.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}