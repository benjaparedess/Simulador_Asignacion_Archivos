#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

// cuanto ocupa un puntero a un bloque (en bytes)
#define PUNTERO 4

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

int main() {
    return 0;
}
