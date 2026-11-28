#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

// cuanto ocupa un puntero a un bloque (en bytes)
#define PUNTERO 4


//un segundo de simulacion en ms
//se puede modificar

#define SEGUNDO_US 1000000

// los tres mecanismos
#define CONTIGUA 1
#define ENLAZADA 2
#define INDEXADA 3

// datos que se piden por input
int disco_mb;
int bloque_kb;
int modo;
int min_kb;
int max_kb;

// el disco: una casilla por bloque, 0 si esta libre
// y si no el numero del archivo que lo ocupa
int num_bloques;
vector<int> disco;

struct Archivo {
    int numero;
    int tam_kb;
    int existe;            // 1 si sigue en el disco, 0 si lo eliminaron
    vector<int> bloques;   // bloques de datos, en el orden del archivo
    vector<int> indices;   // bloques indice (solo en indexada)
};

vector<Archivo> archivos;

// muestra el error y termina el programa
void error(string mensaje) {
    cout << "Dato invalido: " << mensaje << endl;
    exit(1);
}

int pedir_numero(string texto) {
    int n;
    cout << texto;
    cin >> n;
    if (cin.fail()) {
        error("hay que escribir un numero");
    }
    return n;
}

// pide los datos de la simulacion y revisa que esten bien
void leer_datos() {
    string nombre;

    disco_mb = pedir_numero("Tamaño del disco (MB): ");
    bloque_kb = pedir_numero("Tamaño de cada bloque (KB): ");
    cout << "Mecanismo de asignación (contigua, enlazada o indexada): ";
    cin >> nombre;
    min_kb = pedir_numero("Tamaño mínimo de los archivos (KB): ");
    max_kb = pedir_numero("Tamaño máximo de los archivos (KB): ");

    if (disco_mb <= 0 || bloque_kb <= 0) {
        error("el disco y el bloque tienen que ser mayores a 0");
    }
    if (bloque_kb > disco_mb * 1024) {
        error("el bloque no puede ser mas grande que el disco");
    }
    if (nombre == "contigua") {
        modo = CONTIGUA;
    } else if (nombre == "enlazada") {
        modo = ENLAZADA;
    } else if (nombre == "indexada") {
        modo = INDEXADA;
    } else {
        error("el mecanismo tiene que ser contigua, enlazada o indexada");
    }
    if (min_kb <= 0 || min_kb > max_kb) {
        error("el rango de archivos tiene que cumplir 0 < minimo <= maximo");
    }
}


// crea un archivo de tamaño aleatorio dentro del rango
void crear_archivo(int seg) {
    Archivo a;
    a.numero = archivos.size() + 1;
    a.tam_kb = min_kb + rand() % (max_kb - min_kb + 1);
    a.existe = 1;
    archivos.push_back(a);
    cout << "[" << seg << " s] Se crea el archivo " << a.numero << " de " << a.tam_kb << " KB" << endl;
}

int main() {
    leer_datos();
    srand(time(NULL));

    cout << "Disco de " << disco_mb << " MB con bloques de " << bloque_kb << " KB" << endl;
    cout << "Archivos de " << min_kb << " a " << max_kb << " KB" << endl;

    // un ciclo por cada segundo de la simulacion
    // por ahora termina a los 10 segundos, despues va a terminar cuando no haya espacio
    for (int seg = 1; seg <= 10; seg++) {
        usleep(SEGUNDO_US);
        if (seg % 2 == 0) {
            crear_archivo(seg);
        }
    }
    return 0;
}
