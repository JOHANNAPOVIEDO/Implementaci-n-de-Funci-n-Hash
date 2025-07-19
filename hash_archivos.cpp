
#include <iostream>
#include <fstream>
using namespace std;

const int TAM_TABLA = 20;

struct Nodo {
    int clave;
    Nodo* sig;
};

Nodo* tablaHash[TAM_TABLA];
int colisiones = 0;
int elementosEnColisiones = 0;

int FuncionHash(int clave, int tamanoTabla) {
    return clave % tamanoTabla;
}

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

void MostrarOcupacion() {
    cout << "\n Ocupación de tabla:\n";
    cout << "Tamaño del Área de Colisiones: " << TAM_TABLA << endl;
    cout << "Número de elementos en área de colisiones: " << elementosEnColisiones << endl;
    float porcentaje = (elementosEnColisiones * 100.0) / TAM_TABLA;
    cout << "Porcentaje de ocupación: " << porcentaje << "%" << endl;
}

void MostrarTabla() {
    cout << "\n Contenido de tabla Hash:\n";
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

// Guardar en archivo de texto
void GuardarEnArchivoTXT(const char* nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error al abrir archivo para guardar.\n";
        return;
    }

    for (int i = 0; i < TAM_TABLA; ++i) {
        Nodo* temp = tablaHash[i];
        while (temp != NULL) {
            archivo << temp->clave << endl;
            temp = temp->sig;
        }
    }

    archivo.close();
    cout << " Datos guardados en archivo TXT.\n";
}

// Cargar desde archivo de texto
void CargarDesdeArchivoTXT(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Archivo no encontrado. Se inicia tabla vacía.\n";
        return;
    }

    int clave;
    while (archivo >> clave) {
        InsertarElemento(clave);
    }

    archivo.close();
    cout << "Datos cargados desde archivo TXT.\n";
}

int main() {
    for (int i = 0; i < TAM_TABLA; ++i) tablaHash[i] = NULL;

    int valores[20] = { 3, 18, 41, 26, 7, 14, 33, 12, 9, 28, 19, 8, 21, 5, 17, 22, 1, 36, 39, 2 };
    int opcion;
    const char* nombreArchivo = "datos_hash.txt";

    do {
        cout << "\n MENÚ DE OPCIONES\n";
        cout << "1. Insertar un elemento manualmente\n";
        cout << "2. Mostrar ocupación\n";
        cout << "3. Mostrar tabla\n";
        cout << "4. Insertar automáticamente 20 elementos\n";
        cout << "5. Guardar en archivo .txt\n";
        cout << "6. Cargar desde archivo .txt\n";
        cout << "7. Salir\nOpción: ";
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
            case 5:
                GuardarEnArchivoTXT(nombreArchivo);
                break;
            case 6:
                CargarDesdeArchivoTXT(nombreArchivo);
                break;
        }
    } while (opcion != 7);

    return 0;
}