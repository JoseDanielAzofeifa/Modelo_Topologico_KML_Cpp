//.h de la clase para crear,escribir y leer archivo 
class arch{
public:	// Variables y funciones de la clase de �mbito p�blico
	arch(){};		// Constructor por defecto
	virtual ~arch(){};		// Destructor

	virtual int crearArchivo(char *filename,char *dato)=0;	// Funci�n para crear el archivo
	virtual int leerArchivo(char *filename)=0;	// Funci�n para leer el archivo
	
};


