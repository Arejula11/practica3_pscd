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

void pasarTestigo(Semaphore& testigo , const int silla, const bool hayFila, Semaphore* rprimero[], Semaphore* rsegundo[], Semaphore& rtercero, Semaphore& rcuarto, Semaphore& rquinto, const int pareja[], const int terminado, const bool examen_fin[], int a[], int b[], int& c, int& d, int&e){
    
    
    for (int i = 0; i < N_EST; i++)
    {
       if (hayFila && pareja[i] && a[i]>0)
       {
        a[i]--;
        rprimero[i]->signal();
       }
       
    }
    for (int i = N_EST; i < N_EST*2; i++)
    {
       if (examen_fin[i] && b[i]>0)
       {
        b[i]--;
        rsegundo[i]->signal();
       }
       
    }
    if (silla<2 && c>0){
        c--;
        rtercero.signal();
    
    }else if(terminado == 30 && d>0){
        d--;
        rcuarto.signal();
    }
    else if(silla == 2 && e>0){
        e--;
        rquinto.signal();
    }else{
        testigo.signal();
    }

}

//----------------------------------------------------
void Estudiante(const int nip,int& fila,  bool& hayFila, int D[N_FIL][N_COL], int& silla, int resultado[], bool examen_fin[],
                int& silla1, int& silla2, int pareja[], Semaphore* rprimero[], Semaphore* rsegundo[], Semaphore& rtercero, Semaphore& rcuarto, Semaphore& rquinto, Semaphore& testigo, int a[], int b[], int& c, int& d, int&e, int& terminado){
    // esperar por una silla libre
    //<await (silla<2) // una de las dos esté libre
   
        testigo.wait();
        
        if(silla>=2){
            c++;
            testigo.signal();
            rtercero.wait();      
            
        }
        silla++;
        if(silla == 0){
            silla1 = nip;
            cout<<silla1;
        }else if(silla == 1){
            silla2 = nip;
            cout<<silla2;
        }
        
        pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, pareja,terminado,examen_fin, a, b, c, d, e);
        
    //> 
    
    //esperar me sea asignada pareja y fila
   // <await (hayFila = true && pareja[nip]>=0 )
        testigo.wait();
    
        if(!hayFila && pareja[nip]<0){
            a[nip]++;
            testigo.signal();
            rprimero[nip]->wait();
            
        }
        int miFila = fila;
        int miPareja = pareja[nip];
        silla = 0; 
        pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, pareja,terminado,examen_fin, a, b, c, d, e);//>
         
        if (nip<miPareja) {
            // calcular máx de mi 
            //<
            resultado[nip] = maxFila(D,miFila); // quitar exclusion mutua
            //hacérselo llegar a mi pareja
            examen_fin[nip]=true; 
            pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, pareja,terminado,examen_fin, a, b, c, d, e);//>
            
        }
        else {
            // calcular la suma de mi fila 
            resultado[nip] = sumaFila(D, miFila);
            //coger info de max (de mi pareja) 
            //<await(examen_fin[miPareja]= true)
            testigo.wait();
            if(!examen_fin[miPareja]){
                b[miPareja]++;
                testigo.signal();
                rsegundo[miPareja]->wait();
            }
            //mostrar resultados
            pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, pareja,terminado,examen_fin, a, b, c, d, e);//> // cambiar couts
            cout << left << setw(6) << to_string(miFila) + "|  " + to_string(miPareja) +"-"<< setw(4)<<nip +  "|  " << setw(7) << to_string(resultado[miPareja]) +"|  " + to_string(resultado[nip]) + '\n';
            //comunicar finalizacíon
            //<
            testigo.wait();
            examen_fin[nip] = true;
            terminado++;
            pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, pareja,terminado,examen_fin, a, b, c, d, e);//>
            //----------------------------------------------------
        } 
}
void Profesor (int& silla, int& silla1, int& silla2, int pareja[], int& fila, bool& hayFila, Semaphore* rprimero[], Semaphore* rsegundo[], Semaphore& rtercero, Semaphore& rcuarto, Semaphore& rquinto, bool examen_fin[],const int terminado, Semaphore& testigo, int a[], int b[], int& c, int& d, int&e){
    
    
    for(int i=0; i<N_FIL; i++) {
        hayFila = false;
        // esperar a que haya dos
        //<await silla = 2
        testigo.wait(); //repasar todos   
        if(silla!=2){
            e++;
            testigo.signal();
            rquinto.wait();
        }
        pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, pareja,terminado,examen_fin, a, b, c, d, e);//>
        //comunicar a cada uno su pareja, y la fila que les toca
        //<
        
        testigo.wait();
        pareja[silla1]= silla2;
        pareja[silla2] = silla1;
        fila = i;
        hayFila = true; 
        pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, pareja,terminado,examen_fin, a, b, c, d, e);//>

     }
    //pensar si mejor fin examen contador y termiando = true cuando el contador sea = 60 pq ahora habria que 
   // esperar que todos hayan terminado
    
    //<await(terminado=30)
    //repasar
        testigo.wait();
        if(terminado!=30){
            d++;
            testigo.signal();
            rcuarto.wait();
            
        }
    pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, pareja,terminado,examen_fin, a, b, c, d, e);
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
    int pareja[N_EST]; //pareja[i] será la pareja asignada 
    for (int i = 0; i < N_EST; i++){
        pareja[i] = -1; // inicializar vector
    }
   
    bool examen_fin[N_EST]; 
    for (int i = 0; i < N_EST; i++){
        examen_fin[i] = false; // inicializar vector
    }

    int silla = 0;  // 0 = 0 sillas ocupadas , 1 = una silla ocupada, 2 = 2 sillas ocupadas
    int silla1; // su valor es el del estudiante sentado
    int silla2; // su valor es el del estudiante sentado
    int resultado[N_EST];
    bool hayFila=false;
    //Semaphore* s3;
    // inicializar
    Semaphore* rprimer[N_EST];
    for (int i = 0; i < N_EST; i++){
        rprimer[i] = new Semaphore(0); // inicializar punteros
    };  
    Semaphore* rsegundo[N_EST];
    Semaphore rtercero(0);
    Semaphore rcuarto(0);
    Semaphore rquinto(0);
    Semaphore testigo(1);
    int a[N_EST];
    for (int i = 0; i < N_EST; i++){
        a[i] = 0; // inicializar vector
    };  
    int b[N_EST];
    for (int i = 0; i < N_EST; i++){
        b[i] = 0; // inicializar vector
    };  
    int c = 0;
    int d = 0;
    int e = 0;
   
    
    int terminado = 0;


    //cargar "datos.txt" en "D"
    leerFich(D);
    thread Estu[60]; // cambiar
    thread Profe;
    
    Profe= thread(&Profesor, ref(silla), ref(silla1), ref(silla2), ref(pareja), ref(fila), ref(hayFila), ref(rprimer),ref(rsegundo),ref(rtercero),ref(rcuarto),ref(rquinto),ref(examen_fin), terminado,ref(testigo), ref(a), ref(b), ref(c), ref(d), ref(e));
   
    for(int i=0; i<N_EST; i++){
        Estu[i]= thread(&Estudiante, i-1, ref(fila), ref(hayFila), ref(D), ref(silla), ref(resultado), ref(examen_fin), ref(silla1), ref(silla2), ref(pareja), ref(rprimer),ref(rsegundo),ref(rtercero),ref(rcuarto),ref(rquinto), ref(testigo) ,ref(a), ref(b), ref(c), ref(d), ref(e), ref(terminado));
    }
    
    Profe.join();
    for (int i = 0; i < N_EST; i++){
        Estu[i].join();//me bloqueo hasta que "P[i]" termine
    }
    for (int i = 0; i < N_EST; i++){
        delete rprimer[i] ; // inicializar punteros
    };  
    for (int i = 0; i < N_EST; i++){
        delete rsegundo[i]; // inicializar punteros
    };  
    cout << "Prueba finalizada\n";
    return 0;

}