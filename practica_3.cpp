#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>
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

void pasarTestigo(Semaphore& testigo,int d[38], const int silla, const bool hayFila, const int pareja[N_EST], const bool terminado){
    if(silla<2 & d[0]>0){

    }else if(hayFila & pareja[0] & d[1]>0){

    }else if(hayFila & pareja[1] & d[2]>0){
        
    }else if(hayFila & pareja[2]& d[3]>0){
        
    }else if(hayFila & pareja[3]& d[4]>0){
        
    }else if(hayFila & pareja[4]& d[5]>0){
        
    }else if(hayFila & pareja[5]& d[6]>0){
        
    }else if(hayFila & pareja[6]& d[7]>0){
        
    }else if(hayFila & pareja[7]& d[8]>0){
        
    }else if(hayFila & pareja[8]& d[9]>0){
        
    }else if(hayFila & pareja[9]& d[10]>0){
        
    }else if(hayFila & pareja[10]& d[11]>0){
        
    }else if(hayFila & pareja[11]& d[12]>0){
        
    }else if(hayFila & pareja[12]& d[13]>0){
        
    }else if(hayFila & pareja[13]& d[14]>0){
        
    }else if(hayFila & pareja[14]& d[15]>0){
        
    }else if(hayFila & pareja[15]& d[16]>0){
        
    }else if(hayFila & pareja[16]& d[17]>0){
        
    }else if(hayFila & pareja[17]& d[18]>0){
        
    }else if(hayFila & pareja[18]& d[19]>0){
        
    }else if(hayFila & pareja[19]& d[20]>0){
        
    }else if(hayFila & pareja[20]& d[21]>0){
        
    }else if(hayFila & pareja[21]& d[22]>0){
        
    }else if(hayFila & pareja[22]& d[23]>0){
        
    }else if(hayFila & pareja[23]& d[24]>0){
        
    }else if(hayFila & pareja[24]& d[25]>0){
        
    }else if(hayFila & pareja[25]& d[26]>0){
        
    }else if(hayFila & pareja[26]& d[27]>0){
        
    }else if(hayFila & pareja[27]& d[28]>0){
        
    }else if(hayFila & pareja[28]& d[29]>0){
        
    }else if(hayFila & pareja[29]& d[30]>0){
        
    }else if(hayFila & pareja[30]& d[31]>0){
        
    }else if(hayFila & pareja[31]& d[32]>0){
        
    }else if(hayFila & pareja[32]& d[33]>0){
        
    }else if(hayFila & pareja[33]& d[34]>0){
        
    }else if(hayFila & pareja[34]& d[35]>0){
        
    }else if(hayFila & pareja[35]& d[36]>0){
        
    }else if(terminado & d[37]>0){

    }else{
        testigo.signal();
    }

}

//----------------------------------------------------
void Estudiante(int nip,int& fila,  bool& hayFila, int D[N_FIL][N_COL], int& silla, int resultado[N_EST], bool examen_fin[N_EST],
                int& silla1, int& silla2, int pareja[], Semaphore r[], Semaphore& testigo, int d[36]){
    // esperar por una silla libre
    //<await (silla<2) // una de las dos esté libre
        silla++;
        if(silla = 0){
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
            //<await(examen_fin[miPareja]= true)>
            //mostrar resultados
            cout<< left << setw(6)<<miFila << "|  " <<miPareja <<"-"<< setw(4)<<nip << "|  "<< setw(7) <<resultado[miPareja]<< "|  "<<resultado[nip]<<endl;
            //comunicar finalizacíon
            //<
            testigo.wait();
            examen_fin[nip] = true;
            //pasarTestigo(testigo, d, silla);
            //>
            //----------------------------------------------------

    } 
}
void Profesor (int& silla, int& silla1, int& silla2, int pareja[N_EST], int& fila, bool& hayFila, Semaphore r[], bool examen_fin[N_EST], bool terminado){
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
    //pensar si mejor fin examen contador y termiando = true cuando el contador sea = 60 pq ahora habria que 
    // esperar que todos hayan terminado
    //<await terminado true (fin_examen[0]= true && fin_examen[1] = true && ...)

    //fin examen 
    //>

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
    bool estu_fin[N_FIL][2] = {false};
    int silla = 0;  // 0 = 0 sillas ocupadas , 1 = una silla ocupada, 2 = 2 sillas ocupadas
    int silla1; // su valor es el del estudiante sentado
    int silla2; // su valor es el del estudiante sentado
    int resultado[N_EST];
    bool hayFila;
    Semaphore* s3;
    Semaphore* r[37];
    Semaphore testigo = 1;
    int d[38]= {0};
    bool terminado;


    //cargar "datos.txt" en "D"
    leerFich(D);
    thread P[61];
    for(int i=0; i<N_EST; i++){
        P[i]= thread(&Estudiante, i, ref(fila), ref(hayFila), D, ref(silla), ref(resultado), ref(examen_fin), ref(silla1), ref(silla2), ref(pareja), ref(r), ref(testigo), ref(d));
    }
    P[60]= thread(&Profesor, ref(silla), ref(silla1), ref(silla2), ref(pareja), ref(fila), ref(hayFila), ref(examen_fin), ref(terminado));
    cout << "Prueba finalizada\n";
    return 0;

}