#include <iostream>
#include <iomanip>
#include <list>

using namespace std;


/*
Estructuras a utilizar
*/

struct posicionCaballo{
    int x;
    int y;
    posicionCaballo(int x, int y){
        this->x = x;
        this->y = y;
    }
};


/*
Declaraciones de funciones
*/
void inicializarMatriz(int matriz[5][5]);

void devolverMovimientosPosibles(posicionCaballo* posicion, list<posicionCaballo*> &movimientosPosibles);

bool podar(posicionCaballo posicion, list<posicionCaballo*> visitados);
int backtracking(list<posicionCaballo*> &solucion,posicionCaballo* posicionActual,int contador, int totalCasilleros);

void imprimirSolucion(list<posicionCaballo*> solucion);
void imprimirMovimientosPosibles(list<posicionCaballo*> movimientosPosibles);


/*
Fin de declaracion
*/


/*
Comienzo del main
*/

int main()
{
    string aux;

    list<posicionCaballo*> solucion;
    posicionCaballo* posicion = (new posicionCaballo(0,0));
    backtracking(solucion,posicion,1,25);
    imprimirSolucion(solucion);
    cout << "----------------" << endl;
    cout << "Ingrese cualquier caracter para salir: ";
    cin >> aux;


    return 0;
}

/*
Fin del main
*/


void inicializarMatriz(int matriz[5][5]){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++)
            matriz[i][j] = 0;
    }
}

void devolverMovimientosPosibles(posicionCaballo* posicion, list<posicionCaballo*> &movimientosPosibles){
    posicionCaballo* movimientos[8];
    posicionCaballo* nodo;
    movimientos[0] = (new posicionCaballo(2,1));
    movimientos[1] = (new posicionCaballo(1,2));
    movimientos[2] = (new posicionCaballo(-2,1));
    movimientos[3] = (new posicionCaballo(-2,-1));
    movimientos[4] = (new posicionCaballo(-1,2));
    movimientos[5] = (new posicionCaballo(-1,-2));
    movimientos[6] = (new posicionCaballo(1,-2));
    movimientos[7] = (new posicionCaballo(2,-1));
    for(int i = 0; i < 8 ; i++){
        nodo = (new posicionCaballo(posicion->x + movimientos[i]->x,posicion->y + movimientos[i]->y));
        if((nodo->x >= 0 & nodo->x < 5) & (nodo->y >= 0 & nodo->y < 5))
            movimientosPosibles.push_back(nodo);
    }
}

void imprimirMovimientosPosibles(list<posicionCaballo*> movimientosPosibles){
    list<posicionCaballo*>::iterator iterador = movimientosPosibles.begin();
    cout << "Movimientos posibles: " << endl;
    posicionCaballo* nodo;
    while(iterador != movimientosPosibles.end()){
        nodo = *iterador;
        cout << "X: " << nodo->x << " ; Y: " << nodo->y << endl;
        iterador++;
    }
}

bool podar(posicionCaballo* posicion, list<posicionCaballo*> visitados){
    list<posicionCaballo*>::iterator iterador = visitados.begin();
    posicionCaballo* nodo;
    while(iterador != visitados.end()){
        nodo = *iterador;
        if(nodo != visitados.back()){
            if((posicion->x == nodo->x) & (posicion->y == nodo->y))
                return true;
        }
        iterador++;
    }
    return false;
}

int backtracking(list<posicionCaballo*> &secuencia,posicionCaballo* posicionActual,int contador, int totalCasilleros){
    if(totalCasilleros + 1  == contador){
        return 1; //Encontre la solucion
    }else{
        int solucion = 0;
        list<posicionCaballo*> posiblesMovimientos;
        devolverMovimientosPosibles(posicionActual,posiblesMovimientos);
        list<posicionCaballo*>::iterator iterador = posiblesMovimientos.begin();
        while((iterador != posiblesMovimientos.end()) & (solucion == 0)){
            secuencia.push_back(posicionActual);
            if(!podar(posicionActual,secuencia)){
                solucion = backtracking(secuencia,*iterador,contador + 1, totalCasilleros);
            }
            if(solucion == 1)
                return 1;
            secuencia.pop_back();
            iterador++;
        }
        if(solucion != 1)
            return 0;
    }
}

void imprimirSolucion(list<posicionCaballo*> solucion){
    int matriz[5][5];
    int contador = 1;

    inicializarMatriz(matriz);

    list<posicionCaballo*>::iterator iterador = solucion.begin();
    posicionCaballo* nodo;

    while(iterador != solucion.end()){
        nodo = *iterador;
        matriz[nodo->y][nodo->x] = contador;
        contador++;
        iterador++;
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5 ; j++){
            if(matriz[i][j] > 9)
                cout << matriz[i][j] << "|";
            else
                cout << matriz[i][j] << " |";
        }
        cout << endl;
    }
}

