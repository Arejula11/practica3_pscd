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

void pasarTestigo(Semaphore& testigo, Semaphore& ,int d[38], const int silla, const bool hayFila, const int pareja[N_EST], const bool terminado){
    if(silla<2 & d[0]>0){
        testigo.signal();
    }else if(hayFila & pareja[0] & d[1]>0){
        testigo.signal();
    }else if(hayFila & pareja[1] & d[2]>0){
        testigo.signal();
    }else if(hayFila & pareja[2]& d[3]>0){
        testigo.signal();
    }else if(hayFila & pareja[3]& d[4]>0){
        testigo.signal();
    }else if(hayFila & pareja[4]& d[5]>0){
        testigo.signal();
    }else if(hayFila & pareja[5]& d[6]>0){
        testigo.signal();
    }else if(hayFila & pareja[6]& d[7]>0){
        testigo.signal();
    }else if(hayFila & pareja[7]& d[8]>0){
        testigo.signal();
    }else if(hayFila & pareja[8]& d[9]>0){
        testigo.signal();
    }else if(hayFila & pareja[9]& d[10]>0){
        testigo.signal();
    }else if(hayFila & pareja[10]& d[11]>0){
        testigo.signal();
    }else if(hayFila & pareja[11]& d[12]>0){
        testigo.signal();
    }else if(hayFila & pareja[12]& d[13]>0){
        testigo.signal();
    }else if(hayFila & pareja[13]& d[14]>0){
        testigo.signal();
    }else if(hayFila & pareja[14]& d[15]>0){
        testigo.signal();
    }else if(hayFila & pareja[15]& d[16]>0){
        testigo.signal();
    }else if(hayFila & pareja[16]& d[17]>0){
        testigo.signal();
    }else if(hayFila & pareja[17]& d[18]>0){
        testigo.signal();
    }else if(hayFila & pareja[18]& d[19]>0){
        testigo.signal();
    }else if(hayFila & pareja[19]& d[20]>0){
        testigo.signal();
    }else if(hayFila & pareja[20]& d[21]>0){
        testigo.signal();
    }else if(hayFila & pareja[21]& d[22]>0){
        testigo.signal();
    }else if(hayFila & pareja[22]& d[23]>0){
        testigo.signal();
    }else if(hayFila & pareja[23]& d[24]>0){
        testigo.signal();
    }else if(hayFila & pareja[24]& d[25]>0){
        testigo.signal();
    }else if(hayFila & pareja[25]& d[26]>0){
        testigo.signal();
    }else if(hayFila & pareja[26]& d[27]>0){
        testigo.signal();
    }else if(hayFila & pareja[27]& d[28]>0){
        testigo.signal();
    }else if(hayFila & pareja[28]& d[29]>0){
        testigo.signal();
    }else if(hayFila & pareja[29]& d[30]>0){
        testigo.signal();
    }else if(hayFila & pareja[30]& d[31]>0){
        testigo.signal();
    }else if(hayFila & pareja[31]& d[32]>0){
        testigo.signal();
    }else if(hayFila & pareja[32]& d[33]>0){
        testigo.signal();
    }else if(hayFila & pareja[33]& d[34]>0){
        testigo.signal();
    }else if(hayFila & pareja[34]& d[35]>0){
        testigo.signal();
    }else if(hayFila & pareja[35]& d[36]>0){
        testigo.signal();
    }else if(hayFila & pareja[36]& d[37]>0){
        testigo.signal();
    }else if(hayFila & pareja[37]& d[38]>0){
        testigo.signal();
    }else if(hayFila & pareja[38]& d[39]>0){
        testigo.signal();
    }else if(hayFila & pareja[39]& d[40]>0){
        testigo.signal();
    }else if(hayFila & pareja[40]& d[41]>0){
        testigo.signal();
    }else if(hayFila & pareja[41]& d[42]>0){
        testigo.signal();
    }else if(hayFila & pareja[42]& d[43]>0){
        testigo.signal();
    }else if(hayFila & pareja[43]& d[44]>0){
        testigo.signal();
    }else if(hayFila & pareja[44]& d[45]>0){
        testigo.signal();
    }else if(hayFila & pareja[45]& d[46]>0){
        testigo.signal();
    }else if(hayFila & pareja[46]& d[47]>0){
        testigo.signal();
    }else if(hayFila & pareja[47]& d[48]>0){
        testigo.signal();
    }else if(hayFila & pareja[48]& d[49]>0){
        testigo.signal();
    }else if(hayFila & pareja[49]& d[50]>0){
        testigo.signal();
    }else if(hayFila & pareja[50]& d[51]>0){
        testigo.signal();
    }else if(hayFila & pareja[51]& d[52]>0){
        testigo.signal();
    }else if(hayFila & pareja[52]& d[53]>0){
        testigo.signal();
    }else if(hayFila & pareja[53]& d[54]>0){
        testigo.signal();
    }else if(hayFila & pareja[54]& d[55]>0){
        testigo.signal();
    }else if(hayFila & pareja[55]& d[56]>0){
        testigo.signal();
    }else if(hayFila & pareja[56]& d[57]>0){
        testigo.signal();
    }else if(hayFila & pareja[57]& d[58]>0){
        testigo.signal();
    }else if(hayFila & pareja[58]& d[59]>0){
        testigo.signal();
    }else if(hayFila & pareja[59]& d[60]>0){
        testigo.signal(); 
    }else if(terminado & d[61]>0){
        testigo.signal();
    }else{
        testigo.signal();
    }

}

//----------------------------------------------------
void Estudiante(int nip,int& fila,  bool& hayFila, int D[N_FIL][N_COL], int& silla, int resultado[N_EST], bool examen_fin[N_EST],
                int& silla1, int& silla2, int pareja[], Semaphore r[], Semaphore& testigo, int d[36], int& terminado){
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
    Semaphore* s3;
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
    cout << "Prueba finalizada\n";
    return 0;

}