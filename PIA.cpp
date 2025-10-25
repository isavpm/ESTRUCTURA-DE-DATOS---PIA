/*EQUIPO 5
Ruben Gerardo Lozano Rodriguez
Laura Isabella Villarreal Pérez Maldonado
José Gabriel Pérez Ramírez
*/
#include "validaciones.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;
//LISTA
struct nodo
{
    string matricula;
    string nombre;
    int edad;
    double promedio;
    string direccion;
    string telefono;
    
    struct nodo *anterior;
    struct nodo *sgte;
};

nodo *inicio = NULL;
nodo *fin = NULL;
//PILA (no se si se pueda usar el mismo nodo de la lista)
struct nodo
{
	string matricula;
    string nombre;
    int edad;
    double promedio;
    string direccion;
    string telefono;
    struct nodo *sgte;
};
//Prototipos de funcion

void altaAlumnos();
void insertarFinal(string matricula, string nombre, int edad, double promedio, string direccion, string telefono);
void mostrarAlumnos();
void ordenarPorMatricula();
void intercambiarNodos(nodo* a, nodo* b);
nodo* buscarPorMatricula(const string& matriculaBuscada);
void bajaAlumnos();
void bajaParcial();
void bajaTotal();
//main
int main()
{
	int menu;
	
	bool validInput = false;
    
    do 
	{
        try 
		{
            cout << "------------SISTEMA DE ALUMNOS-----------" << endl;
            cout << "1- Alta de alumnos" << endl << "2- Baja de alumnos" << endl 
                 << "3- Recuperar alumnos" << endl << "4- Reportes" << endl 
                 << "5- Inscripciones" << endl << "6- Salir" << endl;
            cout << "Ingrese una opcion(1-6): " << endl;
            
            cin >> menu;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            if (cin.fail()) 
			{
				//si se ingresa algo diferente a un numero lanza la excepcion
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                throw runtime_error("Entrada invalida. Por favor ingrese un numero.");
            }
            if (menu < 1 || menu > 6) 
                throw out_of_range("Opcion fuera de rango. Ingrese un numero entre 1 y 6.");
                
        	if (cin.fail()) 
			{
			    throw runtime_error("Error al limpiar el buffer.");
			}
            validInput = true;
            
        } catch (const exception& e) 
		{
            cout << "Error: " << e.what() << endl;
        }
        switch(menu)
        {
        	case 1:
        		cout<<"Alta de alumnos"<<endl;
        		altaAlumnos();
        	break;
        	case 2:
        		cout<<"Baja de alumnos"<<endl;
        		bajaAlumnos();
        	break;
        	case 3:
        		cout<<"Recuperar alumnos"<<endl;
        	break;
        	case 4:
        		cout<<"Reportes"<<endl;
        		mostrarAlumnos();
        	break;
        	case 5:
        		cout<<"Inscripciones"<<endl;
        	break;
		}
    } while (!validInput || menu!=6);
	
}
//funciones
void altaAlumnos()
{
	bool matriculaExiste = true;
    string matricula;
    string nombre;
    int edad;
    double promedio;
    bool validInput = false;
    string direccion;
    string telefono;
    
    // Matricula 
     do
    {
        matriculaExiste = false; 
        cout << "Ingrese la matricula del alumno(7 numeros): ";
        
        cin.clear();
        getline(cin, matricula);
        
        if(!validarMatricula(matricula)) {
            cout << "Ingrese una matricula valida." << endl;
            continue; 
        }
            
        
        if(buscarPorMatricula(matricula) != NULL) {
            cout << "Ya hay un alumno registrado con la misma matricula. " << endl;
            matriculaExiste = true;
        }
            
    } while(!validarMatricula(matricula) || matriculaExiste);
    
    // Nombre
    do
    {
        cout << "Ingrese el nombre y apellido del alumno: ";
        cin.clear();
        getline(cin, nombre);
        
        if(!validarNombre(nombre))
            cout << "Favor de ingresar un nombre valido(no numeros ni caracteres especiales)." << endl;
            
    } while(!validarNombre(nombre));
    
    //edad 
    do
    {
    	try 
    	{
    		cout<<"Ingrese la edad del alumno: ";
    		cin>>edad;
    		if (cin.fail()) 
			{
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                throw runtime_error("Entrada invalida. Por favor ingrese un numero.");
            }
            if (edad < 16) 
                throw out_of_range("La edad debe ser mayor a 16");
                
    		validInput = true;
		}catch (const exception& e) 
		{
            cout << "Error: " << e.what() << endl;
        }
	}while(!validInput);
	
	//promedio
	validInput = false;
	do
    {
    	try 
    	{
    		cout<<"Ingrese el promedio general del alumno: ";
    		cin>>promedio;
    		if (cin.fail()) 
			{
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                throw runtime_error("Entrada invalida. Por favor ingrese un numero.");
            }
            if (promedio < 0 || promedio > 100) 
                throw out_of_range("El promedio debe estar entre 0 y 100");
                
    		validInput = true;
		}catch (const exception& e) 
		{
            cout << "Error: " << e.what() << endl;
        }
	}while(!validInput);
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	//direccion
	do
	{
		cout<<"Ingrese la direccion del alumno: ";
		cin.clear();
		getline(cin, direccion);
		if(!validarDireccion(direccion))
			cout<<"Ingrese una direccion valida(solo numeros y letras)"<<endl;
	}while(!validarDireccion(direccion));
	
	//telefono
	do
	{
		cout<<"Ingrese el numero de telefono del alumno: ";
		cin.clear();
		getline(cin, telefono);
		if(!validarTelefono(telefono))
			cout<<"El numero tiene que tener 10 digitos."<<endl;
	}while(!validarTelefono(telefono));
	
	//se agrega a la lista y despues se aplica el metodo de ordenamiento...
	insertarFinal(matricula, nombre, edad, promedio, direccion, telefono);
	ordenarPorMatricula();
	
	cout << "Alumno agregado exitosamente!" << endl;
}

void insertarFinal(string matricula, string nombre, int edad, double promedio, string direccion, string telefono) 
{
    // Crear nuevo nodo
    nodo *nuevo = new nodo();
    
    // Asignar datos al nuevo nodo
    nuevo->matricula = matricula;
    nuevo->nombre = nombre;
    nuevo->edad = edad;
    nuevo->promedio = promedio;
    nuevo->direccion = direccion;
    nuevo->telefono = telefono;
    nuevo->sgte = NULL;
    nuevo->anterior = NULL;
    
    // Si la lista está vacía
    if (inicio == NULL) 
    {
        inicio = nuevo;
        fin = nuevo;
    }
    else 
    {
        // Insertar al final
        fin->sgte = nuevo;
        nuevo->anterior = fin;
        fin = nuevo;
    }
}

void intercambiarNodos(nodo* a, nodo* b) {
    // Intercambiar todos los datos entre los nodos
    string tempMatricula = a->matricula;
    string tempNombre = a->nombre;
    int tempEdad = a->edad;
    double tempPromedio = a->promedio;
    string tempDireccion = a->direccion;
    string tempTelefono = a->telefono;
    
    a->matricula = b->matricula;
    a->nombre = b->nombre;
    a->edad = b->edad;
    a->promedio = b->promedio;
    a->direccion = b->direccion;
    a->telefono = b->telefono;
    
    b->matricula = tempMatricula;
    b->nombre = tempNombre;
    b->edad = tempEdad;
    b->promedio = tempPromedio;
    b->direccion = tempDireccion;
    b->telefono = tempTelefono;
}

void ordenarPorMatricula() {
    if (inicio == NULL || inicio->sgte == NULL) {
        // Lista vacía o con un solo elemento, ya está ordenada
        return;
    }
    
    bool swapped;
    nodo* ptr1;
    nodo* lptr = NULL;
    
    // Implementación de Bubble Sort
    do {
        swapped = false;
        ptr1 = inicio;
        
        while (ptr1->sgte != lptr) {
            // Comparar matrículas como strings
            if (ptr1->matricula > ptr1->sgte->matricula) {
                intercambiarNodos(ptr1, ptr1->sgte);
                swapped = true;
            }
            ptr1 = ptr1->sgte;
        }
        lptr = ptr1;
    } while (swapped);
    
    cout << "Lista ordenada por matricula exitosamente!" << endl;
}

void mostrarAlumnos() 
{
    if (inicio == NULL) 
    {
        cout << "No hay alumnos registrados." << endl;
        return;
    }
    
    nodo *actual = inicio;
    int contador = 1;
    
    cout << "\n--- LISTA DE ALUMNOS (ORDENADA POR MATRICULA) ---" << endl;
    while (actual != NULL) 
    {
        cout << "Alumno #" << contador << ":" << endl;
        cout << "Matricula: " << actual->matricula << endl;
        cout << "Nombre: " << actual->nombre << endl;
        cout << "Edad: " << actual->edad << endl;
        cout << "Promedio: " << actual->promedio << endl;
        cout << "Direccion: " << actual->direccion << endl;
        cout << "Telefono: " << actual->telefono << endl;
        cout << "------------------------" << endl;
        
        actual = actual->sgte;
        contador++;
    }
}

// Función de búsqueda binaria para la lista 
nodo* buscarPorMatricula(const string& matriculaBuscada) {
    if (inicio == NULL) {
        return NULL;
    }
    
    nodo* izquierda = inicio;
    nodo* derecha = fin;
    
    while (izquierda != NULL && derecha != NULL && izquierda != derecha->sgte) {
        // Calcular el nodo medio
        nodo* medio = izquierda;
        nodo* temp = izquierda;
        int contador = 0;
        
        // Contar nodos entre izquierda y derecha
        while (temp != NULL && temp != derecha->sgte) {
            contador++;
            temp = temp->sgte;
        }
        
        // Mover al nodo medio
        int medioIndex = contador / 2;
        for (int i = 0; i < medioIndex; i++) {
            medio = medio->sgte;
        }
        
        // Comparar
        if (medio->matricula == matriculaBuscada) {
            return medio;
        }
        else if (medio->matricula < matriculaBuscada) {
            izquierda = medio->sgte;
        }
        else {
            derecha = medio->anterior;
        }
    }
    
    // Verificar el último nodo
    if (izquierda != NULL && izquierda->matricula == matriculaBuscada) {
        return izquierda;
    }
    return NULL;
}

void bajaAlumnos()
{
	int menu;
	bool validInput = false;
	do
	{
		try
		{
		
			cout<<"-----------BAJA DE ALUMNOS------------"<<endl;
			cout<<"1- Baja Parcial"<<endl<<"2- Baja total"<<endl<<"3- Regresar al menu"<<endl;
			cout<<"Selecciona una opcion(1-2): ";
			
			cin >> menu;
			cout<<menu;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            if (cin.fail()) 
			{
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                throw runtime_error("Entrada invalida. Por favor ingrese un numero.");
            }
            if (menu < 1 || menu > 3) 
                throw out_of_range("Opcion fuera de rango. Ingrese un numero entre 1 y 3.");
            validInput = true;
		}catch (const exception& e) 
		{
            cout << "Error: " << e.what() << endl;
        }
        switch(menu)
        {
        	case 1:
        		//Baja Parcial(Apilar)
        	break;
        	case 2:
        		//Baja Total(Borrar directamente de la lista)
        	break;
		}
	}while(!validInput || menu != 3);
}

void bajaParcial()
{
	//pregunta por una matricula o un nombre, si es matricula es busqueda binaria y si es nombre busqueda secuencial
	
}
void bajaTotal()
{
	//pregunta por una matricula o un nombre, si es matricula es busqueda binaria y si es nombre busqueda secuencial
	
}
