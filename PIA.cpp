/*EQUIPO 5
Ruben Gerardo Lozano Rodriguez
Laura Isabella Villarreal Perez Maldonado
Jose Gabriel P?rez Ram?rez
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
//PILA 
struct pilaParcial
{
	string matricula;
    string nombre;
    int edad;
    double promedio;
    string direccion;
    string telefono;
    struct pilaParcial *sgte;
};
pilaParcial* tope = NULL;

//COLA
struct inscripcion 
{
    string matricula;
    string nombre;
    int edad;
    double promedio;
    string direccion;
    string telefono;
    inscripcion* sgte;
};
inscripcion* frente = NULL;
inscripcion* finalCola = NULL;


//Prototipos de funcion
void altaAlumnos();
void insertarFinal(string matricula, string nombre, int edad, double promedio, string direccion, string telefono);
void mostrarAlumnos();
void ordenarPorMatricula();
void intercambiarNodos(nodo* a, nodo* b);
nodo* buscarPorMatricula(const string& matriculaBuscada);
nodo* buscarPorNombre(const string& nombreBuscado);
void bajaAlumnos();
void bajaParcial();
void bajaTotal();
void insertPilaParcial(nodo* alumno);
void eliminarDeLista(nodo* alumno);
void inscripciones();
void encolar(inscripcion*& frente, inscripcion*& finalCola, nodo* alumno);
void ordenarCola();
inscripcion* desencolar(inscripcion*& frente, inscripcion*& finalCola);
void encolar(inscripcion*& frente, inscripcion*& finalCola, nodo* alumno);
void recuperarAlumno();
bool pilaVacia();
pilaParcial* popPilaParcial();
void menuReportes();
void reporteActivos();
void reporteInactivos();
void reporteAprobadosReprobados();
void reporteTop3();
void reportePromedioGeneral();
void reporteDistribucionRangos();


//MAIN
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
                cout << "Recuperar alumnos" << endl;
                recuperarAlumno();
            break;

        	case 4:
        		cout << "Reportes" << endl;
                menuReportes();
        	break;
        	case 5:
        		cout<<"Inscripciones"<<endl;
        		inscripciones();
        	break;
		}
    } while (!validInput || menu!=6);

}
//FUNCIONES
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

        if(!validarMatricula(matricula)) 
		{
            cout << "Ingrese una matricula valida." << endl;
            continue;
        }


        if(buscarPorMatricula(matricula) != NULL) 
		{
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

    // Si la lista esta vacia
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

void intercambiarNodos(nodo* a, nodo* b) 
{
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

void ordenarPorMatricula()
{
    if (inicio == NULL || inicio->sgte == NULL) 
	{
        // Lista vacia o con un solo elemento, ya esta ordenada
        return;
    }

    bool swapped;
    nodo* ptr1;
    nodo* lptr = NULL;

    // Implementacion de Bubble Sort
    do 
	{
        swapped = false;
        ptr1 = inicio;

        while (ptr1->sgte != lptr) 
		{
            // Comparar matriculas como strings
            if (ptr1->matricula > ptr1->sgte->matricula) 
			{
                intercambiarNodos(ptr1, ptr1->sgte);
                swapped = true;
            }
            ptr1 = ptr1->sgte;
        }
        lptr = ptr1;
    } while (swapped);

    cout << "Lista ordenada por matricula exitosamente!" << endl;
}

void reporteActivos()
{
    if (inicio == NULL)
    {
        cout << "No hay alumnos registrados." << endl;
        return;
    }

    nodo *actual = inicio;
    int contador = 1;

    cout << "\n--- LISTA DE ALUMNOS ---" << endl;
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

// Funcion de busqueda binaria para la lista
nodo* buscarPorMatricula(const string& matriculaBuscada) 
{
    if (inicio == NULL) 
	{
        return NULL;
    }

    nodo* izquierda = inicio;
    nodo* derecha = fin;

    while (izquierda != NULL && derecha != NULL && izquierda != derecha->sgte) 
	{
        // Calcular el nodo medio
        nodo* medio = izquierda;
        nodo* temp = izquierda;
        int contador = 0;

        // Contar nodos entre izquierda y derecha
        while (temp != NULL && temp != derecha->sgte) 
		{
            contador++;
            temp = temp->sgte;
        }

        // Mover al nodo medio
        int medioIndex = contador / 2;
        for (int i = 0; i < medioIndex; i++) 
		{
            medio = medio->sgte;
        }

        // Comparar
        if (medio->matricula == matriculaBuscada) 
		{
            return medio;
        }
        else if (medio->matricula < matriculaBuscada) 
		{
            izquierda = medio->sgte;
        }
        else 
		{
            derecha = medio->anterior;
        }
    }

    // Verificar el ultimo nodo
    if (izquierda != NULL && izquierda->matricula == matriculaBuscada)
	{	
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
        		bajaParcial();
        	break;
        	case 2:
        		bajaTotal();
        	break;
		}
	}while(!validInput || menu != 3);
}

void bajaParcial()
{


	//pregunta por una matricula o un nombre, si es matricula es busqueda binaria y si es nombre busqueda secuencial
	if (inicio == NULL) 
	{
        cout << "No hay alumnos registrados." << endl;
        return;
    }

    int opcion;
    string matricula, nombre;
    nodo* encontrado = NULL;

    do 
	{
        cout << "----- BAJA PARCIAL -----" << endl;
        cout << "1- Buscar por matricula" << endl;
        cout << "2- Buscar por nombre" << endl;
        cout << "3- Regresar" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (cin.fail())
			{
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Entrada invalida. Por favor ingrese un numero.");
            }

        if (opcion == 1) 
		{
            cout << "Ingrese la matricula del alumno: ";
            getline(cin, matricula);
            encontrado = buscarPorMatricula(matricula);
        }
        else if (opcion == 2) 
		{
            cout << "Ingrese el nombre del alumno: ";
            getline(cin, nombre);
            encontrado = buscarPorNombre(nombre);
        }
        else if (opcion == 3) 
		{
            cout << "Regresando al menu anterior" << endl;
            break;
        }
        else 
		{
            cout << "Opcion fuera de rango. Intente de nuevo." << endl;
            continue;
        }

        if (encontrado != NULL) 
		{
            cout << "\nAlumno encontrado: " << encontrado->nombre << endl;
            cout << "Matricula: " << encontrado->matricula << endl;

            insertPilaParcial(encontrado);       // Guardar en la pilaParcial
            eliminarDeLista(encontrado); // Eliminar de la lista

            cout << "El alumno ha sido dado de baja parcial."<< endl;
            break;
        } else if (opcion != 3) 
		{
            cout << "No se encontro el alumno." << endl;
        }

    } while (opcion != 3);
}

void bajaTotal() 
{
    if (inicio == NULL) 
	{
        cout << "No hay alumnos registrados." << endl;
        return;
    }

    int opcion;
    string matricula, nombre;
    nodo* encontrado = NULL;

    do 
	{
        cout << "----- BAJA TOTAL -----" << endl;
        cout << "1- Buscar por matricula" << endl;
        cout << "2- Buscar por nombre" << endl;
        cout << "3- Regresar" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (cin.fail())
			{
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Entrada invalida. Por favor ingrese un numero.");
            }

        if (opcion == 1) 
		{
            cout << "Ingrese la matricula del alumno: ";
            getline(cin, matricula);
            encontrado = buscarPorMatricula(matricula);
        }
        else if (opcion == 2) 
		{
            cout << "Ingrese el nombre del alumno: ";
            getline(cin, nombre);
            encontrado = buscarPorNombre(nombre);
        }
        else if (opcion == 3) 
		{
            cout << "Regresando al menu anterior" << endl;
            break;
        }
        else 
		{
            cout << "Opcion fuera de rango. Intente de nuevo." << endl;
            continue;
        }

        if (encontrado != NULL) 
		{
            cout << "\nAlumno encontrado: " << encontrado->nombre << endl;
            cout << "Matricula: " << encontrado->matricula << endl;

            eliminarDeLista(encontrado);
            cout << "El alumno ha sido eliminado permanentemente de la lista." << endl << endl;
            break;
        } else if (opcion != 3) 
		{
            cout << "No se encontro el alumno." << endl;
        }

    } while (opcion != 3);
}

void eliminarDeLista(nodo* alumno) 
{
    if (alumno == NULL) return;

    if (alumno == inicio) inicio = alumno->sgte;
    if (alumno == fin) fin = alumno->anterior;
    if (alumno->anterior) alumno->anterior->sgte = alumno->sgte;
    if (alumno->sgte) alumno->sgte->anterior = alumno->anterior;

    delete alumno;
}

void insertPilaParcial(nodo* alumno) 
{
    pilaParcial* nuevo = new pilaParcial();
    nuevo->matricula = alumno->matricula;
    nuevo->nombre = alumno->nombre;
    nuevo->edad = alumno->edad;
    nuevo->promedio = alumno->promedio;
    nuevo->direccion = alumno->direccion;
    nuevo->telefono = alumno->telefono;
    nuevo->sgte = tope;
    tope = nuevo;
}

nodo* buscarPorNombre(const string& nombreBuscado) 
{
    nodo* actual = inicio;
    while (actual != NULL) 
	{
        if (actual->nombre == nombreBuscado)
            return actual;
        actual = actual->sgte;
    }
    return NULL;
}

void encolar(inscripcion*& frente, inscripcion*& finalCola, nodo* alumno) 
{
    inscripcion* nuevo = new inscripcion();
    nuevo->matricula = alumno->matricula;
    nuevo->nombre = alumno->nombre;
    nuevo->edad = alumno->edad;
    nuevo->promedio = alumno->promedio;
    nuevo->direccion = alumno->direccion;
    nuevo->telefono = alumno->telefono;
    nuevo->sgte = NULL;

    if (finalCola == NULL) 
	{
        frente = finalCola = nuevo;
    } else 
	{
        finalCola->sgte = nuevo;
        finalCola = nuevo;
    }
}
inscripcion* desencolar(inscripcion*& frente, inscripcion*& finalCola) 
{
    if (frente == NULL) return NULL;
    inscripcion* temp = frente;
    frente = frente->sgte;
    if (frente == NULL) finalCola = NULL;
    temp->sgte = NULL;
    return temp;
}


void ordenarCola() 
{
    if (inicio == NULL) 
	{
        cout << "No hay alumnos registrados.\n";
        return;
    }

    nodo* copiaLista = NULL;
    nodo* actual = inicio;


    while (actual != NULL) 
	{
        nodo* nuevo = new nodo();
        *nuevo = *actual;
        nuevo->sgte = copiaLista;
        copiaLista = nuevo;
        actual = actual->sgte;
    }


    bool swapped;
    nodo* ptr1;
    nodo* lptr = NULL;
    do 
	{
        swapped = false;
        ptr1 = copiaLista;
        while (ptr1->sgte != lptr) 
		{
            nodo* next = ptr1->sgte;
            if (ptr1->promedio < next->promedio ||
                (ptr1->promedio == next->promedio && ptr1->nombre > next->nombre)) 
			{
                intercambiarNodos(ptr1, next);
                swapped = true;
            }
            ptr1 = ptr1->sgte;
        }
        lptr = ptr1;
    } while (swapped);


    actual = copiaLista;
    while (actual != NULL) 
	{
        encolar(frente, finalCola, actual);
        actual = actual->sgte;
    }


    actual = copiaLista;
    while (actual != NULL) 
	{
        nodo* aux = actual;
        actual = actual->sgte;
        delete aux;
    }
}

bool pilaVacia() 
{
    return tope == NULL;
}

pilaParcial* popPilaParcial() 
{
    if (tope == NULL) return NULL;
    pilaParcial* nodo = tope;
    tope = tope->sgte;
    nodo->sgte = NULL;
    return nodo;
}

void recuperarAlumno() 
{
    if (pilaVacia()) 
    {
        cout << "No hay alumnos en baja parcial para recuperar." << endl;
        return;
    }

    // desapila el ultimo alumno dado de baja parcial
    pilaParcial* rec = popPilaParcial();

    // 3) Defensa: si por alguna razón ya existe esa matrícula activa, no duplicar.
    //    (Esto “rompe” el intento de insertar duplicados a propósito).
    if (buscarPorMatricula(rec->matricula) != NULL) 
	{
        cout << "Advertencia: ya existe un alumno activo con la misma matricula ("
             << rec->matricula << "). Se cancela la recuperacion para evitar duplicados." << endl;
        // Regresar el nodo a la pila para no perderlo
        rec->sgte = tope;
        tope = rec;
        return;
    }

    // 4) Insertar al final y reordenar por matrícula para mantener la invariante
    insertarFinal(rec->matricula, rec->nombre, rec->edad, rec->promedio, rec->direccion, rec->telefono);
    ordenarPorMatricula();

    cout << "Alumno recuperado: " << rec->nombre << " (" << rec->matricula << ")" << endl;

    // 5) Liberar el contenedor temporal de la pila (ya clonamos los datos en la lista)
    delete rec;
}


void inscripciones() 
{
    if (inicio == NULL)
	{
        cout << "No hay alumnos activos para inscribir.\n";
        return;
    }

    ordenarCola();

    int numGrupos;
    cout << "Ingrese el numero de grupos a crear: ";
    cin >> numGrupos;

    // Contar alumnos en la cola
    int totalAlumnos = 0;
    inscripcion* temp = frente;
    while (temp != NULL) 
	{
        totalAlumnos++;
        temp = temp->sgte;
    }

    if (numGrupos <= 0 || totalAlumnos == 0) 
	{
        cout << "Datos inv?lidos.\n";
        return;
    }

    int base = totalAlumnos / numGrupos;
    int extra = totalAlumnos % numGrupos;

    cout << "\nInscripciones\n";

    int grupoActual = 1;
    int alumnosEnGrupo = 0;
    int limiteGrupo;

    // Si sobran alumnos, los primeros grupos tendran uno mas
    if (extra > 0)
        limiteGrupo = base + 1;
    else
        limiteGrupo = base;


    while (frente != NULL) 
	{
        inscripcion* alumno = desencolar(frente, finalCola);

        if (alumnosEnGrupo == 0) 
		{
            cout << "\nGrupo " << grupoActual << ":\n";
        }

        cout << "  - " << alumno->nombre << " (" << alumno->promedio << ")\n";

        alumnosEnGrupo++;

        if (alumnosEnGrupo == limiteGrupo) 
		{
	        grupoActual++;
	        alumnosEnGrupo = 0;
	
	
	        if (extra > 0) 
			{
	            extra--;
	            limiteGrupo = base + 1;
	        } else 
			{
	            limiteGrupo = base;
	        }
    	}
        delete alumno;
    }
    cout << "\n=== Todos los alumnos fueron inscritos ===\n";
}
void menuReportes()
{
    int op;
    bool validInput = false;

    do
    {
        try
        {
            cout << "\n===== REPORTES =====" << endl;
            cout << "1- Alumnos activos (lista)" << endl;
            cout << "2- Alumnos inactivos (pila)" << endl;
            cout << "3- Aprobados / Reprobados (%)" << endl;
            cout << "4- Top 3 promedios" << endl;
            cout << "5- Promedio general" << endl;
            cout << "6- Rangos (90-100,80-89,70-79,<70)" << endl;
            cout << "7- Regresar" << endl;
            cout << "Ingrese una opcion (1-7): " << endl;

            cin >> op;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Entrada invalida. Por favor ingrese un numero.");
            }
            if (op < 1 || op > 7)
            {
                throw out_of_range("Opcion fuera de rango. Ingrese un numero entre 1 y 7.");
            }

            validInput = true;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << endl;
        }

        switch (op)
        {
            case 1:
                reporteActivos();
            break;
            case 2:
                reporteInactivos();
            break;
            case 3:
                reporteAprobadosReprobados();
            break;
            case 4:
                reporteTop3();
            break;
            case 5:
                reportePromedioGeneral();
            break;
            case 6:
                reporteDistribucionRangos();
            break;
        }
    } while (!validInput || op != 7);
}

void reporteInactivos()
{
    if (tope == NULL)
    {
        cout << "No hay alumnos inactivos en baja parcial (pila vacia)." << endl;
        return;
    }

    cout << "\n--- ALUMNOS INACTIVOS ---" << endl;

    pilaParcial* p = tope;
    int i = 1;

    while (p != NULL)
    {
        cout << "Inactivo #" << i << ":" << endl;
        cout << "Matricula: " << p->matricula << endl;
        cout << "Nombre: " << p->nombre << endl;
        cout << "Edad: " << p->edad << endl;
        cout << "Promedio: " << p->promedio << endl;
        cout << "Direccion: " << p->direccion << endl;
        cout << "Telefono: " << p->telefono << endl;
        cout << "------------------------" << endl;

        p = p->sgte;  
        i++;
    }
}

void reporteAprobadosReprobados()
{
    if (inicio == NULL)
    {
        cout << "No hay alumnos activos." << endl;
        return;
    }

    int total = 0;
    int apr = 0;
    int rep = 0;

    nodo* a = inicio;
    while (a != NULL)
    {
        total++;
        if (a->promedio >= 70.0) 
            apr++;
        else 
            rep++;
        a = a->sgte;
    }

    double pApr = (total > 0) ? (apr * 100.0 / total) : 0.0;
    double pRep = (total > 0) ? (rep * 100.0 / total) : 0.0;

    cout << "\n--- APROBADOS / REPROBADOS ---" << endl;
    cout << "Total activos: " << total << endl;
    cout << "Aprobados: " << apr << " (" << pApr << "%)" << endl;
    cout << "Reprobados: " << rep << " (" << pRep << "%)" << endl;
}

void reporteTop3()
{
    if (inicio == NULL)
    {
        cout << "No hay alumnos activos." << endl;
        return;
    }

    string m1 = "", m2 = "", m3 = "";
    string n1 = "", n2 = "", n3 = "";
    double p1 = -1.0, p2 = -1.0, p3 = -1.0;

    nodo* a = inicio;
    while (a != NULL)
    {
        if (a->promedio > p1)
            p1 = a->promedio; n1 = a->nombre; m1 = a->matricula;
        a = a->sgte;
    }

    a = inicio;
    while (a != NULL)
    {
        if (a->matricula != m1 && a->promedio > p2)
            p2 = a->promedio; n2 = a->nombre; m2 = a->matricula;
        a = a->sgte;
    }

    a = inicio;
    while (a != NULL)
    {
        if (a->matricula != m1 && a->matricula != m2 && a->promedio > p3)
            p3 = a->promedio; n3 = a->nombre; m3 = a->matricula;
        a = a->sgte;
    }

    cout << "\n--- TOP 3 PROMEDIOS ---" << endl;
    int rank = 1;
    if (p1 >= 0.0) { cout << rank << ") " << n1 << " (" << m1 << ")  " << p1 << endl; rank++; }
    if (p2 >= 0.0) { cout << rank << ") " << n2 << " (" << m2 << ")  " << p2 << endl; rank++; }
    if (p3 >= 0.0) { cout << rank << ") " << n3 << " (" << m3 << ")  " << p3 << endl; rank++; }
    if (rank == 1) { cout << "No hay suficientes alumnos." << endl; }
}

void reportePromedioGeneral()
{
    if (inicio == NULL)
    {
        cout << "No hay alumnos activos." << endl;
        return;
    }

    int total = 0;
    double suma = 0.0;

    nodo* a = inicio;
    while (a != NULL)
    {
        suma += a->promedio;
        total++;
        a = a->sgte;
    }

    double media = (total > 0) ? (suma / total) : 0.0;

    cout << "\n--- PROMEDIO GENERAL ---" << endl;
    cout << "Alumnos: " << total << endl;
    cout << "Media: " << media << endl;
}

void reporteDistribucionRangos()
{
    if (inicio == NULL)
    {
        cout << "No hay alumnos activos." << endl;
        return;
    }

    int r90 = 0;
    int r80 = 0;
    int r70 = 0;
    int rMenor70 = 0;
    int total = 0;

    nodo* a = inicio;
    while (a != NULL)
    {
        double p = a->promedio;
        total++;

        if (p >= 90.0) r90++;
        else if (p >= 80.0) r80++;
        else if (p >= 70.0) r70++;
        else rMenor70++;

        a = a->sgte;
    }

    double pct90 = (total > 0) ? (r90 * 100.0 / total) : 0.0;
    double pct80 = (total > 0) ? (r80 * 100.0 / total) : 0.0;
    double pct70 = (total > 0) ? (r70 * 100.0 / total) : 0.0;
    double pctM  = (total > 0) ? (rMenor70 * 100.0 / total) : 0.0;

    cout << "\n--- DISTRIBUCION POR RANGOS ---" << endl;
    cout << "90-100: " << r90 << " (" << pct90 << "%)" << endl;
    cout << "80-89 : " << r80 << " (" << pct80 << "%)" << endl;
    cout << "70-79 : " << r70 << " (" << pct70 << "%)" << endl;
    cout << "< 70  : " << rMenor70 << " (" << pctM  << "%)" << endl;
}
