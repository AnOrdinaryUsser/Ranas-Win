#include <stdio.h> 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include "ranas.h"

#define HOR_MIN 0
#define HOR_MAX 79
#define VER_MIN 0
#define VER_MAX 11

//(Y = 0 y 3) == antes de cruzar el río.
//(Y = 11)    == orilla


/* Punteros a las funciones */
BOOL * AvanceRana(int*, int*, int);
BOOL * AvanceRanaFin(int, int);
BOOL * AvanceRanaIni(int, int);
BOOL * AvanceTroncos(int i);
BOOL * ComprobarEstadIsticas(LONG, LONG, LONG);
BOOL * FinRanas(void);
BOOL * InicioRanas(int, int*, int*, int*, int, TIPO_CRIAR);
BOOL * PartoRanas(int);
void * Pausa(void);
BOOL * PuedoSaltar(int, int, int);
void * PrintMsg(char*);

//FUNCIONES
void tratarArg(int argc, char* argv[]);
int cargarRanas();

//MAIN
int main(int argc, char* argv[])
{
	/*
	HANDLE hilo1, hilo2;
	CHAR char1, char2;
	DWORD id1, id2;
	INT i, reps;
	
	*/

	//TRATAMIENTO ARGUMENTOS
	tratarArg(argc, argv);

	if (cargarRanas() == -1) {
		PERROR("Error al cargar la biblioteca ranas.");
		exit(2);
	}

	/*
	//PRIORIDAD DEL PROCESO NORMAL --> IDLE
	if (SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS) == false) {
		PERRORR("SetPriorityClass");
		return 1;
	}

	//CREACIÓN HILO 1
	hilo1 = CreateThread(NULL, 0, funcionHilo1, (void*)reps, NULL, &id1);
	if (SetThreadPriority(hilo1, THREAD_PRIORITY_HIGHEST) == false) {
		PERRORR("SetThreadPriority");
		return 1;
	}

	//CREACIÓN HILO 2
	hilo2 = CreateThread(NULL, 0, funcionHilo2, (void*)reps, NULL, &id2);
	if (SetThreadPriority(hilo2, THREAD_PRIORITY_HIGHEST) == false) {
		PERRORR("SetThreadPriority");
		return 1;
	}

	//BUCLE DEL PADRE
	for (i = 0; i < reps; i++)
	{
		printf("0");
		fflush(stdout);
	}

	Sleep(4000); //Para que el padre no se muera, chapuza
	//Para esperar a los hijos 
	*/
	return 0;
}

//FUNCION TRATAR ARGUMENTOS
void tratarArg(int argc, char * argv[]) {

int param1, param2;


if(argc != 3) {
	fprintf(stderr,"%s\n","USO: ./ranas VELOCIDAD VELOCIDAD_PARTO");
	exit(1);
}

param1 = atoi(argv[1]);
param2 = atoi(argv[2]);

if(param1 < 0 || param1 > 1000) {
	fprintf(stderr,"%s\n","Ha introducido una velocidad incorrecta.\nPor favor, introduzca una velocidad ente 0 y 1000.");
	exit(1);
}

if (param2 <= 0) {
	fprintf(stderr, "%s\n", "Ha introducido un tiempo de partos incorrecto.\nIntroduzca un tiempo mayor de 0.");
	exit(1);
}

}


//FUNCION CARGAR LIBRERIA RANAS.DLL
int cargarRanas() {
	HINSTANCE controladorDll;

	controladorDll = LoadLibrary("ranas.dll");
	if (NULL == controladorDll) {
		fprintf(stderr, "%s\n", "ErrorLoadLibrary");
		return -1;
	}

	BOOL InicioRanas(int delta_t, int lTroncos[], int lAguas[], int dirs[], int t_Criar, TIPO_CRIAR f_Criar);
}

/*
//FUNCION DEL HILO 1
DWORD WINAPI funcionHilo1(LPVOID argumento) {
	INT i, reps;
	//...
	return 0;
}

//FUNCION DEL HILO 2
DWORD WINAPI funcionHilo2(LPVOID argumento) {
	INT i, reps;
	//...
	return 0;
}
*/