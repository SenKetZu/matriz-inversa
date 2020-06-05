#include <iostream>
#include "rlutil.h"
#include <iomanip>


using namespace std;

// la variable es el numero a contar
int contar(float numero) {

    int len = 0;
    if (numero != 0) {
        
        int enteros = int(numero);
        int decimales = int((numero - enteros) * 1000000);
        
        if (decimales != 0) {
            len++;
            while (decimales % 10 == 0) {
                decimales /= 10;
            }
            len += to_string(decimales).length();
        }
        len += to_string(enteros).length();
        
    }
    else {
        len = 1;
    }

    return len;
}

/**el primer argumento es la matriz, el segundo es la fila a modificar, el tercero
   es la fila que usas para modficar, el cuarto es el ancho de la matriz
   osea el largo de las filas   **/
void sumarFilasMatriz(float** a, int b, int c, int d) {

    for (int k = 0; k < d; k++) {

        a[b][k] += a[c][k];

    }
}

// El priemr argumento es la matriz, el segundo es la fila, el tercero es el ancho
void transformarDiagonalDeFilaEnUno(float** a,int b, int d) {
    if (a[b][b]!=0) {
        
        float numOrig = a[b][b];
        for (int j = 0 ; j < d; j++) {

            a[b][j] *= 1.0f/(numOrig);
            if (a[b][j] == 0) {
               a[b][j] = 0;
            }
        }
    }
    
}

// El priemr argumento es la matriz, el segundo es la fila,el tercero es el numero
// el cuarto es el largo de la matriz
void multiplicarFilaPorNumero(float** a,int b, int c,int d) {

    for (int i = 0; i < d;i++) {
        a[b][d] *= c;
    }
}

//a= matriz, bxd es el tamaño de la matriz, x,y son la posicion
void mostrarMatriz(float** a,int b, int d, int x, int y) {
    int cant;
    for (int i = 0; i < b; i++) {
        for (int o = 0, j = 1; o < d; o++, j += 2) {

            cant = contar(a[i][o]);
            if (o>b) {
                j++;
                rlutil::locate(j + x, i + y);
                cout << "|[" << a[i][o] << "]";
                j += cant;
                
            }
            rlutil::locate(j+x, i + y);
            cout << "[" << a[i][o] << "]";
            j += cant;

        }
        cout << endl;
    }
}



int main() {
    //----------------------------------------inicio----------------------------------------//
    int orden, cant,largoTotal,transcicion=0;

    float entrada=0,numeroPorMult=1.0f;
    cout << "Ingrese el orden de la matriz: ";

    cin >> orden;
    largoTotal = orden * 2;



    float** m = new float* [orden];

    for (int i = 0; i < orden; i++) {
        m[i] = new float[largoTotal];
    }
    //relleno la matriz con ceros
    for (int f = 0; f < orden; f++) {
        for (int c = 0; c < largoTotal; c++) {
                
            m[f][c] = 0.0f;
                        
        }
    }
    //------------------------------------------------------------------------------------------
    
    system("cls");
    
    //bucle rellenar y mostrar la matriz 
    for (int f = 0; f < orden; f++) {
        for (int c = 0; c < orden; c++) {
            
            mostrarMatriz(m,orden,orden,0,5);            

         //-----------------------------------------ingreso numeros-----------------
            rlutil::locate(1, 1);
            cout << "ingrese los numeros: ";
            cin >> entrada;
            
            m[f][c] = entrada;            

            system("cls");

        }
    }    
    
    //---------------------GAUS YORDAN----------------------------------   
    //crear identidad
    for (int f = 0; f < orden; f++) {
        for (int c = orden; c < largoTotal; c++) {
            
            //aca se llena la diagonal con 1 el resto con 0 de la matriz identidad
            if (f+orden==c) {
                m[f][c] = 1;
            }
            else {
                m[f][c] = 0;
            }
        }
    }
    //determinante
    /**
    for (int i = 0; i < orden; i++) {
        for (int j = 0; j < orden; j++) {

            if (j != i) {

                numeroPorMult = (m[j][i]);

                for (int k = 0; k < largoTotal; k++) {
                    if (k<j) {
                        m[j][k] -= ((m[i][k]) * numeroPorMult);
                    }
                    

                }
            }
        }
    }
    **/
    //
    /////////Paso 1 transformar el numero C1,1  en un 1 haciendo c1,1/c1,1

    //este bucle pasa por las columnas
    for (int i = 0; i < orden;i++) {
        
        //transforma el elemento diagonnal en 1 y toda la fila:-------------        
        if (m[i][i] != 0&& m[i][i]!=1) {
                    
            transformarDiagonalDeFilaEnUno(m,i,largoTotal);

        }                                        
        
        // i = que fila es la que tiene la diagonal/la que tengo que multiplicar y sumarla a la que estoy recorriendo
        // j= va bajando por las filas
        // k= va apsando por als columnas
        //---------------------------------------------------------------------------        
        for (int j = 0; j < orden; j++) {  
                                                                                                                                             
            if (j != i) {
                
                numeroPorMult = (m[j][i]);
                
                for (int k = 0; k < largoTotal; k++) {                    
                                                                                       
                    m[j][k] -= ((m[i][k]) * numeroPorMult);                            
                                                                                       
                }
            }        
        }           
    }
    
    //muestra matriz    
    mostrarMatriz(m, orden, largoTotal, 0, 10);
   

    system("pause");
    return 0;
}
