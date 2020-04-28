#include <stdio.h> 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include "ranas.h"

#define HOR_MIN 0
#define HOR_MAX 79
#define VER_MIN 0
#define VER_MAX 11

//CREAR STRUCT IPC RANAS
HINSTANCE globalRanasDLL;

//(Y = 0 y 3) == antes de cruzar el río.
//(Y = 11)    == orilla


/* Punteros a las funciones */
BOOL (* AvanceRana1)(int*, int*, int);
BOOL (* AvanceRanaFin1)(int, int);
BOOL (* AvanceRanaIni1)(int, int);
BOOL (* AvanceTroncos1)(int i);
BOOL (* ComprobarEstadIsticas1)(LONG, LONG, LONG);
BOOL (* FinRanas1)(void);
BOOL (* InicioRanas1)(int, int*, int*, int*, int, TIPO_CRIAR);
BOOL (* PartoRanas1)(int);
void (* Pausa1)(void);
BOOL (* PuedoSaltar1)(int, int, int);
void (* PrintMsg1)(char*);

//FUNCIONES
void tratarArg(int argc, char* argv[]);
int cargarRanas();

//MAIN
int main(int argc, char* argv[])
{
	system("mode con:cols=80 lines=25"); //FIJA AUTOMÁTICAMENTE A 80x25
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
	
	Sleep(5000);
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
	HINSTANCE ranasDLL;

	ranasDLL = LoadLibrary("ranas.dll");
	if (NULL == ranasDLL) {
		PERROR("Error al cargar ranas.dll (LoadLibrary).");
		return -1;
	}

	globalRanasDLL = ranasDLL; //Guardamos el puntero del fichero DLL

	AvanceRana1 = (BOOL(*)(int *,int *,int)) GetProcAddress(ranasDLL, "AvanceRana");
	if (AvanceRana1 == NULL) {
		PERROR("Error en GetProcAddress: AvanceRana.");
		return -1;
	}

	AvanceRanaFin1 = (BOOL(*)(int, int)) GetProcAddress(ranasDLL, "AvanceRanaFin");
	if (AvanceRanaFin1 == NULL) {
		PERROR("Error en GetProcAddress: AvanceRanaFin.");
		return -1;
	}

	AvanceRanaIni1 = (BOOL(*)(int, int)) GetProcAddress(ranasDLL, "AvanceRanaIni");
	if (AvanceRanaIni1 == NULL) {
		PERROR("Error en GetProcAddress: AvanceRanaIni.");
		return -1;
	}

	AvanceTroncos1 = (BOOL(*)(int i)) GetProcAddress(ranasDLL, "AvanceTroncos");
	if (AvanceTroncos1 == NULL) {
		PERROR("Error en GetProcAddress: AvanceTroncos.");
		return -1;
	}

	ComprobarEstadIsticas1 = (BOOL(*)(LONG, LONG, LONG)) GetProcAddress(ranasDLL, "ComprobarEstadIsticas");
	if (ComprobarEstadIsticas1 == NULL) {
		PERROR("Error en GetProcAddress: ComprobarEstadIsticas.");
		return -1;
	}

	FinRanas1 = (BOOL(*)(void)) GetProcAddress(ranasDLL, "FinRanas");
	if (FinRanas1 == NULL) {
		PERROR("Error en GetProcAddress: FinRanas.");
		return -1;
	}

	InicioRanas1 = (BOOL(*)(int, int*, int*, int*, int, TIPO_CRIAR)) GetProcAddress(ranasDLL, "InicioRanas");
	if (InicioRanas1 == NULL) {
		PERROR("Error en GetProcAddress: InicioRanas.");
		return -1;
	}

	PartoRanas1 = (BOOL(*)(int)) GetProcAddress(ranasDLL, "PartoRanas");
	if (PartoRanas1 == NULL) {
		PERROR("Error en GetProcAddress: PartoRanas.");
		return -1;
	}
	Pausa1 = (void(*)(void)) GetProcAddress(ranasDLL, "Pausa");
	if (Pausa1 == NULL) {
		PERROR("Error en GetProcAddress: Pausa.");
		return -1;
	}

	PuedoSaltar1 = (BOOL(*)(int, int, int)) GetProcAddress(ranasDLL, "PuedoSaltar");
	if (PuedoSaltar1 == NULL) {
		PERROR("Error en GetProcAddress: PuedoSaltar.");
		return -1;
	}
	
	PrintMsg1 = (void(*)(char*)) GetProcAddress(ranasDLL, "PrintMsg");
	if (PrintMsg1 == NULL) {
		PERROR("Error enGetProcAddress: PrintMsg.");
		return -1;
	}

	return 0;
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