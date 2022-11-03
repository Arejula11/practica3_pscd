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

void pasarTestigo(Semaphore& testigo ,int d[], const int silla, const bool hayFila, Semaphore* r[], const int pareja[], const int terminado, const bool examen_fin[]){
    
    
    for (int i = 0; i < N_EST; i++)
    {
       if (hayFila && pareja[i] && d[i]>0)
       {
        d[i]--;
        r[i]->signal();
       }
       
    }
    for (int i = N_EST; i < N_EST*2; i++)
    {
       if (examen_fin[i] && d[i]>0)
       {
        d[i]--;
        r[i]->signal();
       }
       
    }
    if (silla<2 && d[120]>0){
        d[120]--;
        r[120]->signal();
    
    }else if(terminado == 30 && d[121]>0){
        d[121]--;
        r[121]->signal();
    }
    else if(silla == 2 && d[122]>0){
        d[122]--;
        r[122]->signal();
    }else{
        testigo.signal();
    }

}

//----------------------------------------------------
void Estudiante(const int nip,int& fila,  bool& hayFila, int D[N_FIL][N_COL], int& silla, int resultado[], bool examen_fin[],
                int& silla1, int& silla2, int pareja[], Semaphore* r[], Semaphore& testigo, int d[], int& terminado){
    // esperar por una silla libre
    //<await (silla<2) // una de las dos esté libre
   
        testigo.wait();
        
        if(silla>=2){
            d[120]++;
            testigo.signal();
            r[120]->wait();      
            
        }
        silla++;
        if(silla == 0){
            silla1 = nip;
            cout<<silla1;
        }else if(silla == 1){
            silla2 = nip;
            cout<<silla2;
        }
        
        pasarTestigo(testigo,d,silla,hayFila,r,pareja,terminado,examen_fin);
        
    //> 
    
    //esperar me sea asignada pareja y fila
   // <await (hayFila = true && pareja[nip]>=0 )
        testigo.wait();
    
        if(!hayFila && pareja[nip]<0){
            d[nip]++;
            testigo.signal();
            r[nip]->wait();
            
        }
        int miFila = fila;
        int miPareja = pareja[nip];
        silla = 0; 
        pasarTestigo(testigo,d,silla,hayFila,r,pareja,terminado,examen_fin);//>
         
        if (nip<miPareja) {
            // calcular máx de mi 
            //<
            testigo.wait();
            resultado[nip] = maxFila(D,miFila);
            //hacérselo llegar a mi pareja
            examen_fin[nip]=true; 
            pasarTestigo(testigo,d,silla,hayFila,r,pareja,terminado,examen_fin);//>
            
        }
        else {
            // calcular la suma de mi fila 
            resultado[nip] = sumaFila(D, miFila);
            //coger info de max (de mi pareja) 
            //<await(examen_fin[miPareja]= true)
            testigo.wait();
            if(!examen_fin[miPareja]){
                d[60+miPareja]++;
                testigo.signal();
                r[60+miPareja]->wait();
            }
            //mostrar resultados
            pasarTestigo(testigo,d,silla,hayFila,r,pareja,terminado,examen_fin);//>
            cout<< left << setw(6)<<miFila << "|  " <<miPareja <<"-"<< setw(4)<<nip << "|  "<< setw(7) <<resultado[miPareja]<< "|  "<<resultado[nip]<<endl;
            //comunicar finalizacíon
            //<
            testigo.wait();
            examen_fin[nip] = true;
            terminado++;
            pasarTestigo(testigo,d,silla,hayFila,r,pareja,terminado,examen_fin);//>
            //----------------------------------------------------
        } 
}
void Profesor (int& silla, int& silla1, int& silla2, int pareja[], int& fila, bool& hayFila, Semaphore* r[], bool examen_fin[],const int terminado, Semaphore& testigo, int d[]){
    cout<<"profesor";
    
    for(int i=0; i<N_FIL; i++) {
        hayFila = false;
        // esperar a que haya dos
        //<await silla = 2
          
        if(silla!=2){
            d[122]++;
            testigo.signal();
            r[122]->wait();
        }
        pasarTestigo(testigo,d,silla,hayFila,r,pareja,terminado,examen_fin);//>
        //comunicar a cada uno su pareja, y la fila que les toca
        //<
        
        testigo.wait();
        pareja[silla1]= silla2;
        pareja[silla2] = silla1;
        fila = i;
        hayFila = true; 
        pasarTestigo(testigo,d,silla,hayFila,r,pareja,terminado,examen_fin);//>

     }
    //pensar si mejor fin examen contador y termiando = true cuando el contador sea = 60 pq ahora habria que 
   // esperar que todos hayan terminado
    
    //<await(terminado=30)
        if(terminado!=30){
            d[121]++;
            testigo.signal();
            r[121]->wait();
            
        }
    pasarTestigo(testigo,d,silla,hayFila,r,pareja,terminado,examen_fin);
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
    cout<<"a";
    int D[N_FIL][N_COL]; //para almacenar los datos
    int fila = 0;  //cada pareja cogerá una
    int pareja[N_EST]={-1}; //pareja[i] será la pareja asignada
    bool examen_fin[N_EST] = {false};
    //bool estu_fin[N_FIL][2] = {false};
    int silla = 0;  // 0 = 0 sillas ocupadas , 1 = una silla ocupada, 2 = 2 sillas ocupadas
    int silla1; // su valor es el del estudiante sentado
    int silla2; // su valor es el del estudiante sentado
    int resultado[N_EST];
    bool hayFila=false;
    //Semaphore* s3;
    Semaphore* r[123];
    Semaphore testigo(1);
    int d[123]= {0};
    int terminado = 0;


    //cargar "datos.txt" en "D"
    leerFich(D);
    thread P[61];
    
    P[0]= thread(&Profesor, ref(silla), ref(silla1), ref(silla2), ref(pareja), ref(fila), ref(hayFila), ref(r),ref(examen_fin), terminado,ref(testigo), ref(d));
   
    for(int i=1; i<=N_EST; i++){
        P[i]= thread(&Estudiante, i-1, ref(fila), ref(hayFila), ref(D), ref(silla), ref(resultado), ref(examen_fin), ref(silla1), ref(silla2), ref(pareja), ref(r), ref(testigo) , ref(d), ref(terminado));
    }
    
    P[0].join();
    for (int i = 0; i < N_EST +1; i++){
        P[i].join();//me bloqueo hasta que "P[i]" termine
    }
    cout << "Prueba finalizada\n";
    return 0;

}