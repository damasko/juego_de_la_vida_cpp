#include <iostream>
#include <vector>
using namespace std;
typedef vector < vector<char> > Matriz;

#include <time.h>
//Esta funcion no es mia
void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void rellena_matriz(Matriz &a) {
    cout << "Rellene el tablero con las celulas iniciales" << endl;
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
    //COPY_A FUNCIONA CORRECTAMENTE, continuar trazas
    int vecinos = 0;
    //i empieza en 1 y es matriz-1 para saltarme los margenes que contienen el cuadro
    for (int i = 1; i < a.size()-1; ++i) {
        for (int j = 1; j < a[0].size()-1; ++j) {
            //Mirar si con un bucle de 3 iteracion desde -1 a 1 iria mejor o un array 3x3. lioso...
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
            else if (vecinos == 2) copy_a[i][j] = a[i][j];
            //En caso de tener 2 vecinos se quedará como está, si esta viva vive si no sigue muerta xD
            vecinos = 0;
        }
    }

    //Se supone que ya tenemos el nuevo array con la nueva generacion, asi que se lo copio al array original, ojala chufle
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
    //Aunque el juego de la vida es infinito lo limito a 20 por ejemplo
    for (int i = 0; i < 20; ++i) {
        dibuja_tablero(a);
        modifica_vector(a);
        sleep(1000);
        cout << string(50, '\n');
    }

}
