#include <iostream>
#include "Semaphore_V4.hpp"

using namespace std;

const int N_EST = 60; //# de estudiantes
const int N_FIL = N_EST/2; //# de filas en la matriz 
const int N_COL = 1000; //# de columnas

//---------------------------------------------------- 
//Pre: <fila> es un  ́ındice de fila de <D>
//Post: devuelve el m ́aximo de la fila <fila>
int maxFila(int D[N_FIL][N_COL],int fila) {
    int max;
    return max;
}


//Pre: <fila> es un  ́ındice de fila de <D>
//Post: devuelve la suma de los els. de la fila <fila> 
int sumaFila(int D[N_FIL][N_COL],int fila) {
    int sum;
    return sum; 
}

//----------------------------------------------------
void Estudiante(int nip,int& fila,  bool& hayFila, int D[N_FIL][N_COL], int& silla, int resultado[N_EST], int fin_examen[N_EST], int& silla1, int& silla2) {
    int miPareja;
    // esperar por una silla libre
    //esperar me sea asignada pareja y fila 
    if (nip<miPareja) {
        // calcular máx de mi fila
        //hacérselo llegar a mi pareja
    }
    else {
        // calcular la suma de mi fila 
        //coger info de max (de mi pareja) 
        //mostrar resultados
        //comunicar finalizaci ́on
        //----------------------------------------------------
    } 
}
void Profesor (int& silla, int& silla1, int& silla2, int pareja[N_EST], int fila, bool& hayFila) {
    for(int i=0; i<N_FIL; i++) {
    // esperar a que haya dos
    //comunicar a cada uno su pareja, y la fila que les toca
    }
    // esperar que todos hayan terminado
}

int main(){
    int D[N_FIL][N_COL]; //para almacenar los datos
    int fila = 0;  //cada pareja coger ́a una
    int pareja[N_EST]; //pareja[i] ser ́a la pareja asignada
    bool examen_fin[N_EST] = {false};
    bool estu_fin[N_FIL][2] = {false};
    int silla = 0;  // 0 = 0 sillas ocupadas , 1 = una silla ocupada, 2 = 2 sillas ocupadas
    int silla1; // su valor es el del estudiante sentado
    int silla2; // su valor es el del estudiante sentado
    int resultado[N_EST];
    bool hayFila;


    //cargar "datos.txt" en "D"
    /*...*/
    cout << "Prueba finalizada\n";
    return 0;

}