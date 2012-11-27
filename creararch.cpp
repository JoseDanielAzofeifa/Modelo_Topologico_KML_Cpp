//clase para crear,escribir y leer archivo 
#include <iostream>
#include <fstream>
#include <string.h>
#include "arch.h"
using namespace std;

class creararch : public arch {
public:
  creararch(){}     // Constructor
  ~creararch() {}       // Destructor
    
  int crearArchivo(char *filename,char *dato){
    ofstream fichero(filename); 
    if ( fichero.bad()) {
         cout << "Error al abrir archivo"<<endl;}
    else{
       for (unsigned int t = 0; t < strlen(dato); t++ ){//escribir archivo
             fichero.put(dato[t] );}
       fichero.close();}
    return 0;}
  
  int leerArchivo(char *filename){ //leer el archivo
    ifstream fichero(filename); 
    if ( fichero.bad()) {
         cout << "Error al abrir archivo"<<endl;}
    else{
       while ( ! fichero.eof() ) {
            cout << (char)fichero.get();}
       fichero.close();}
    return 0;}
};


