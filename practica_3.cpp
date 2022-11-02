#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>
#include "material_apoyo/librerias/Semaphore_V4/Semaphore_V4.hpp"

using namespace std;

const int N_EST = 60; //# de estudiantes
const int N_FIL = N_EST/2; //# de filas en la matriz 
const int N_COL = 1000; //# de columnas

//---------------------------------------------------- 
//Pre: <fila> es un  ́ındice de fila de <D>
//Post: devuelve el m ́aximo de la fila <fila>
int maxFila(int D[N_FIL][N_COL],int fila) {
    int max;
    for(int i=0; i<N_COL; i++){
        if(max<D[fila][i]){
            max=D[fila][i];
        }
    }
    return max;
}


//Pre: <fila> es un  ́ındice de fila de <D>
//Post: devuelve la suma de los els. de la fila <fila> 
int sumaFila(int D[N_FIL][N_COL],int fila) {
    int sum = 0;
    for (int i = 0; i < N_COL; i++)
    {
        sum += D[fila][i];
    }
    
    return sum; 
}

void pasarTestigo(Semaphore& testigo ,int d[38], const int silla, const bool hayFila, Semaphore* r[62], const int pareja[N_EST], const bool terminado){
    
    
    for (int i = 0; i < N_EST; i++)
    {
       if (hayFila && pareja[i] && d[i]>0)
       {
        d[i]--;
        r[i]->signal();
       }
       
    }
    if (silla<2 && d[61]>0){
        d[61]--;
        r[61]->signal();
    }else if(terminado && d[62]>0){
        d[62]--;
        r[62]->signal();
    }else{
        testigo.signal();
    }

}

//----------------------------------------------------
void Estudiante(int nip,int& fila,  bool& hayFila, int D[N_FIL][N_COL], int& silla, int resultado[N_EST], bool examen_fin[N_EST],
                int& silla1, int& silla2, int pareja[], Semaphore* r[], Semaphore& testigo, int d[36], int& terminado){
    // esperar por una silla libre
    //<await (silla<2) // una de las dos esté libre
        silla++;
        if(silla == 0){
            silla1 = nip;
        }else{
            silla2 = nip;
        }
    //> 
    
    //esperar me sea asignada pareja y fila
   // <await (hayFila = true && pareja[nip]>=0 )
        int miFila = fila;
        int miPareja = pareja[nip];
        silla = 0; //>
                
        if (nip<miPareja) {
            // calcular máx de mi 
            //<
            testigo.wait();
            resultado[nip] = maxFila(D,miFila);
            //hacérselo llegar a mi pareja
            examen_fin[nip]=true; 
            //pasarTestigo(testigo,d,silla);//>
        }
        else {
            // calcular la suma de mi fila 
            resultado[nip] = sumaFila(D, miFila);
            //coger info de max (de mi pareja) 
            //<await(examen_fin[miPareja]= true)
            //mostrar resultados>
            cout<< left << setw(6)<<miFila << "|  " <<miPareja <<"-"<< setw(4)<<nip << "|  "<< setw(7) <<resultado[miPareja]<< "|  "<<resultado[nip]<<endl;
            //comunicar finalizacíon
            //<
            testigo.wait();
            examen_fin[nip] = true;
            terminado++;
            //pasarTestigo(testigo, d, silla);
            //>
            //----------------------------------------------------

    } 
}
void Profesor (int& silla, int& silla1, int& silla2, int pareja[N_EST], int& fila, bool& hayFila, Semaphore r[], bool examen_fin[N_EST],const int terminado){
    for(int i=0; i<N_FIL; i++) {
        // esperar a que haya dos
        //<await silla = 2>
        //comunicar a cada uno su pareja, y la fila que les toca
        //<
        pareja[silla1]= silla2;
        pareja[silla2] = silla1;
        fila = i;
        hayFila = true; //>

    }
    // pensar si mejor fin examen contador y termiando = true cuando el contador sea = 60 pq ahora habria que 
    // esperar que todos hayan terminado
    
    //<await(terminado=30)
            //fin examen>

}

void leerFich(int D[N_FIL][N_COL]){
    ifstream f("material_apoyo/datos.txt");
    if(f.is_open()){
        for(int i=0; i<N_FIL; i++){
            for(int j=0; j<N_COL; j++){ 
                f >> D[i][j];
            }
        }
        f.close();
    }else{
        cout << "No se ha podido abrir el fichero datos.txt" << endl;
    }
}


int main(){
    int D[N_FIL][N_COL]; //para almacenar los datos
    int fila = 0;  //cada pareja cogerá una
    int pareja[N_EST]={-1}; //pareja[i] será la pareja asignada
    bool examen_fin[N_EST] = {false};
    //bool estu_fin[N_FIL][2] = {false};
    int silla = 0;  // 0 = 0 sillas ocupadas , 1 = una silla ocupada, 2 = 2 sillas ocupadas
    int silla1; // su valor es el del estudiante sentado
    int silla2; // su valor es el del estudiante sentado
    int resultado[N_EST];
    bool hayFila;
    // Semaphore* s3;
    Semaphore* r[62];
    Semaphore testigo(1);
    int d[62]= {0};
    int terminado = 0;


    //cargar "datos.txt" en "D"
    leerFich(D);
    thread P[61];
    for(int i=0; i<N_EST; i++){
        P[i]= thread(&Estudiante, i, ref(fila), ref(hayFila), D, ref(silla), ref(resultado), ref(examen_fin), ref(silla1), ref(silla2), ref(pareja), ref(r), ref(testigo), ref(d), ref(terminado));
    }
    P[60]= thread(&Profesor, ref(silla), ref(silla1), ref(silla2), ref(pareja), ref(fila), ref(hayFila), ref(examen_fin), terminado);
    
    for (int i = 0; i < N_EST; i++){
         P[i].join();//me bloqueo hasta que "P[i]" termine
    }
    P[60].join();
    cout << "Prueba finalizada\n";
    return 0;

}