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
    int max = D[fila][0];
    for(int i=1; i<N_COL; i++){
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
    for (int i = 0; i < N_COL; i++){
        sum += D[fila][i];
    }
    return sum; 
}

void pasarTestigo(Semaphore& testigo , const int silla, const bool hayFila, Semaphore* rprimero[], Semaphore& rsegundo, Semaphore& rtercero, Semaphore& rcuarto, Semaphore& rquinto, Semaphore& rsexto, const int pareja[],  int& terminado, const bool examen_fin[], int a[], int& b, int& c, int& d, int&e, int& f, int& levantado){
    bool  ifComple = false;
    for (int i = 0; i < N_FIL; i++){
       if ( examen_fin[i] && a[i]>0){
        a[i]--;
        rprimero[i]->signal();
        ifComple = true;
       }  
    }
    if(!ifComple){
       if (hayFila && b>0 ){
            b--;
            rsegundo.signal();
        }else if (silla<2 && c>0){
            c--;
            rtercero.signal();
        }else if(terminado == 60 && d>0){
            d--;
            rcuarto.signal();
        }else if(silla == 2 && e>0){
            e--;
            rquinto.signal();
        }else if(levantado == 2 && f>0){
            f--;
            rsexto.signal();
        }else{
            testigo.signal();
        }
    } 
}

//----------------------------------------------------
void Estudiante(const int nip,int& fila,  bool& hayFila, int D[N_FIL][N_COL], int& silla, int resultado[], bool examen_fin[],
                int& silla1, int& silla2, int pareja[], Semaphore* rprimero[], Semaphore& rsegundo, Semaphore& rtercero, Semaphore& rcuarto, Semaphore& rquinto, Semaphore& rsexto, Semaphore& testigo, int a[], int& b, int& c, int& d, int&e, int& f, int& terminado, int& levantado){
    // esperar por una silla libre
    //<await (silla<2)  (una de las dos esté libre)
    int miFila;
    int miPareja;
    testigo.wait();
    if(silla>=2){
        c++;
        testigo.signal();
        rtercero.wait();           
    }   
    if(silla == 0){
        silla1 = nip;
        silla++;
    }else if(silla == 1){
           silla2 = nip;
           silla++;
    }
    pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, rsexto, pareja,terminado,examen_fin, a, b, c, d, e,f, levantado);   //> 

    //esperar me sea asignada pareja y fila
    // <await (hayFila = true )
    testigo.wait();
    if(!hayFila){
        b++;
        testigo.signal();
        rsegundo.wait();   
    }
    miFila = fila;
    miPareja = pareja[nip];
    levantado++;
    pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, rsexto, pareja,terminado,examen_fin, a, b, c, d, e,f, levantado);
    if (nip<miPareja) {
        // calcular máx de mi 
        resultado[nip] = maxFila(D,miFila); 
        //hacérselo llegar a mi pareja
        examen_fin[miFila]=true; 
        
    }else {
        // calcular la suma de mi fila 
        resultado[nip] = sumaFila(D, miFila);
        //coger info de max (de mi pareja) 
        //<await(examen_fin[miPareja]= true)
        testigo.wait();
        if(!examen_fin[miFila] ){
            a[miFila]++;
            testigo.signal();
            rprimero[miFila]->wait();
        }
        //mostrar resultados
        pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, rsexto, pareja,terminado,examen_fin, a, b, c, d, e, f, levantado);//> // cambiar couts
        cout << to_string(miFila) + "|  " + to_string(miPareja) + "-" + to_string(nip) +  "|  " + to_string(resultado[miPareja]) +"|  " + to_string(resultado[nip]) + '\n';

        } 
        //comunicar finalizacíon
        //<
        testigo.wait();
        terminado++;
        pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, rsexto, pareja,terminado,examen_fin, a, b, c, d, e, f, levantado);//>
        
}

//----------------------------------------------------
void Profesor (int& silla, int& silla1, int& silla2, int pareja[], int& fila, bool& hayFila, Semaphore* rprimero[], Semaphore& rsegundo, Semaphore& rtercero, Semaphore& rcuarto, Semaphore& rquinto, Semaphore& rsexto, bool examen_fin[], int& terminado, Semaphore& testigo, int a[], int& b, int& c, int& d, int&e, int& f, int& levantado){
    for(int i=0; i<N_FIL; i++) { 
        // esperar a que haya dos
        //<await silla = 2
        testigo.wait(); 
        if(silla!=2){
            e++;
            testigo.signal();
            rquinto.wait();
        }
        //comunicar a cada uno su pareja, y la fila que les toca
        pareja[silla1]= silla2;
        pareja[silla2] = silla1;
        fila = i;
        hayFila = true; 
        pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, rsexto, pareja,terminado,examen_fin, a, b, c, d, e,f, levantado);//>       
        testigo.wait();
        if(levantado != 2){
            f++;
            testigo.signal();
            rsexto.wait();
        }
        silla = 0; 
        hayFila = false;
        levantado = 0;
        pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, rsexto, pareja,terminado,examen_fin, a, b, c, d, e,f, levantado);//>        

        }
        // esperar que todos hayan terminado
        //<await(terminado=30)
    testigo.wait();
    if(terminado!=60){
        d++;
        testigo.signal();
        rcuarto.wait();
        
    }
    pasarTestigo(testigo,silla,hayFila,rprimero, rsegundo, rtercero, rcuarto, rquinto, rsexto, pareja,terminado,examen_fin, a, b, c, d, e, f, levantado);//>
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
    bool examen_fin[N_FIL]; 
    for (int i = 0; i < N_FIL; i++){
        examen_fin[i] = false; // inicializar vector
    }
    int terminado = 0;
    
    int levantado=0;
    int silla = 0;  // 0 = 0 sillas ocupadas , 1 = una silla ocupada, 2 = 2 sillas ocupadas
    int silla1; // su valor es el del estudiante sentado
    int silla2; // su valor es el del estudiante sentado
    int resultado[N_EST];
    bool hayFila=false;

    Semaphore* rprimer[N_EST];
    for (int i = 0; i < N_EST; i++){
        rprimer[i] = new Semaphore(0); // inicializar punteros
    };  
    Semaphore rsegundo(0);
    Semaphore rtercero(0);
    Semaphore rcuarto(0);
    Semaphore rquinto(0);
    Semaphore rsexto(0);
    Semaphore testigo(1);

    int a[N_EST];
    for (int i = 0; i < N_EST; i++){
        a[i] = 0; // inicializar vector
    };  
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
   
    //cargar "datos.txt" en "D"
    leerFich(D);
    thread Estu[60]; 
    thread Profe;
    
    Profe= thread(&Profesor, ref(silla), ref(silla1), ref(silla2), ref(pareja), ref(fila), ref(hayFila), ref(rprimer),ref(rsegundo),ref(rtercero),ref(rcuarto),ref(rquinto), ref(rsexto), ref(examen_fin), ref(terminado),ref(testigo), ref(a), ref(b), ref(c), ref(d), ref(e), ref(f), ref(levantado));
   
    for(int i=0; i<N_EST; i++){
        Estu[i]= thread(&Estudiante, i, ref(fila), ref(hayFila), ref(D), ref(silla), ref(resultado), ref(examen_fin), ref(silla1), ref(silla2), ref(pareja), ref(rprimer),ref(rsegundo),ref(rtercero),ref(rcuarto),ref(rquinto), ref(rsexto),ref(testigo) ,ref(a), ref(b), ref(c), ref(d), ref(e), ref(f), ref(terminado), ref(levantado));
    }
    
    Profe.join();
    for (int i = 0; i < N_EST; i++){
        Estu[i].join();//me bloqueo hasta que "P[i]" termine
    }
     for (int i = 0; i < N_EST; i++){
        delete rprimer[i] ; 
    };  
    cout<<'\n';
    cout << "Prueba finalizada\n";
    return 0;

}