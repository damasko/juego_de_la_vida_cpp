#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

typedef vector < vector<char> > Matriz; 

void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void rellena_matriz(Matriz &a) {
    cout << "Rellene el tablero con las celulas iniciales 1(vivas) o 0(muertas)" << endl;
    cout << endl;  
    cout << "Ej: tablero 3x3" << endl;
    cout << "1 0 1" << endl 
         << "0 1 0" << endl 
         << "1 1 0" << endl; 
    cout << endl;
    
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[0].size(); ++j) {
            if (i == 0 or i == a.size()-1) a[i][j] = '=';
            else if (j == 0 or j == a[0].size()-1) a[i][j] = '|';
            else cin >> a[i][j];
        }
    }
}

void dibuja_tablero(Matriz &a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[0].size(); ++j) {
            if (i == 0 or i == a.size()-1) cout << a[i][j] << "=";
            else if (j == 0 or j == a[0].size()-1){
                if (j == 0) cout << a[i][j] << "|" << " ";
                else cout << a[i][j] << "|";
            }
            else cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void modifica_vector(Matriz &a) {
    Matriz copy_a = a; 
    int vecinos = 0;
    //i empieza en 1 y es matriz-1 para saltarme los margenes que contienen el cuadro
    for (int i = 1; i < a.size()-1; ++i) {
        for (int j = 1; j < a[0].size()-1; ++j) {
            //comprobacion del estado de las celulas adyacentes
            if (a[i-1][j-1] == '1') ++vecinos;
            if (a[i-1][j] == '1') ++vecinos;
            if (a[i-1][j+1] == '1') ++vecinos;
            if (a[i][j+1] == '1') ++vecinos;
            if (a[i+1][j+1] == '1') ++vecinos;
            if (a[i+1][j] == '1') ++vecinos;
            if (a[i+1][j-1] == '1') ++vecinos;
            if (a[i][j-1] == '1') ++vecinos;
            if (vecinos > 3 or vecinos == 1 or vecinos == 0) copy_a[i][j] = '0';
            //En estos casos muere irremediablemente :(
            else if (vecinos == 3) copy_a[i][j] = '1';
            //Ya que tanto si esta viva como si esta muerta al siguiente turno vivira si vale 3
            else copy_a[i][j] = a[i][j]; //para 2 vecinos
            //En caso de tener 2 vecinos se quedar� como est�, si esta viva vive si no sigue muerta xD
            vecinos = 0;
        }
    }

    //Ya tenemos el array copia con la nueva generacion, asi que sobreescribo al array original con este.
    a = copy_a;

}

int main() {

    int largo, alto;
    cout << "Indique largo del tablero" << endl;
    cin >> largo;
    largo = largo + 2;
    cout << "Indique alto del tablero" << endl;
    cin >> alto;
    alto = alto + 2;
    Matriz a (largo, vector<char> (alto));
    rellena_matriz(a);
    cout << string(50, '\n');
    //Aunque el juego de la vida es infinito lo limito a 30 por ejemplo
    for (int i = 0; i < 30; ++i) {
        cout << string(50, '\n');
        dibuja_tablero(a);
        modifica_vector(a);
        sleep(1000);
    }

}
