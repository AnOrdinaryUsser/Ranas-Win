#include <stdio.h> 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include "ranas.h"

#define HOR_MIN 0
#define HOR_MAX 79
#define VER_MIN 0
#define VER_MAX 11
#define MSG_ERROR "GetProcAddress Error."

/*
struct ranasInicio {
	//delta_t: valor del tic de reloj en milisegundos.
	int delta_t;
	//lTroncos : array de siete enteros que contiene el valor de la longitud media de los troncos para cada fila.
	//El índice cero del array se refiere a la fila superior de troncos.
	int lTroncos[];
	//lAguas : Referido a la longitud media del espacio entre troncos.
	int lAguas[];
	//dirs : Cada elemento puede valer DERECHA(0) o IZQUIERDA(1), indicando la dirección en que se moverán los troncos.
	int dirs[];
	//t_Criar : tiempo de reposo entre dos partos, expresado en tics.
	int t_Criar;
	//f_Criar : puntero a la función de rellamada que será invocada cada vez que una rana madre deba reproducirse.
	//El prototipo de la función tiene que ser de modo que devuelva void y reciba un argumento entero, la posición de la rana madre que debe parir.
	TIPO_CRIAR f_Criar;
};*/


//(Y = 0 y 3) == antes de cruzar el río.
//(Y = 11)    == orilla

/* Punteros a las funciones */
typedef BOOL(* AvanceRana)(int*, int*, int);
typedef BOOL(* AvanceRanaFin)(int, int);
typedef BOOL(* AvanceRanaIni)(int, int);
typedef BOOL(* AvanceTroncos)(int i);
typedef BOOL(* ComprobarEstadIsticas)(LONG, LONG, LONG);
typedef BOOL(* FinRanas)(void);
typedef BOOL(* InicioRanas)(int, int*, int*, int*, int, TIPO_CRIAR);
typedef BOOL(* PartoRanas)(int);
typedef void(* Pausa)(void);
typedef BOOL(* PuedoSaltar)(int, int, int);
typedef void(* PrintMsg)(char*);

struct funcionesDLL {
	HINSTANCE ranasDLL;
	AvanceRana avanceRana;
	AvanceRanaIni avanceRanaIni;
	AvanceRanaFin avanceRanaFin;
	AvanceTroncos avanceTroncos;
	ComprobarEstadIsticas comprobarEstadisticas;
	FinRanas finRanas;
	InicioRanas inicioRanas;
	PartoRanas partoRanas;
	PuedoSaltar puedoSaltar;
} funciones;

//FUNCIONES
void tratarArg(int argc, char* argv[], int*, int*);
int cargarRanas();
int error(BOOL, const char *);

//MAIN
int main(int argc, char* argv[])
{
	system("mode con:cols=80 lines=25"); //FIJA AUTOMÁTICAMENTE A 80x25

	/*HANDLE hilo1, hilo2;
	CHAR char1, char2;
	DWORD id1, id2;
	INT i, reps;
	*/
	int *velocidad, *parto;

	//TRATAMIENTO ARGUMENTOS
	tratarArg(argc, argv, velocidad, parto);

	if (cargarRanas() == -1) {
		PERROR("Error al cargar la biblioteca ranas.");
		exit(2);
	}



	/*
	//PRIORIDAD DEL PROCESO NORMAL --> IDLE
	if (SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS) == false) {
		PERROR("SetPriorityClass");
		return 1;
	}

	//CREACIÓN HILO 1
	hilo1 = CreateThread(NULL, 0, funcionHilo1, (void*)reps, NULL, &id1);
	if (SetThreadPriority(hilo1, THREAD_PRIORITY_HIGHEST) == false) {
		PERROR("SetThreadPriority");
		return 1;
	}

	//CREACIÓN HILO 2
	hilo2 = CreateThread(NULL, 0, funcionHilo2, (void*)reps, NULL, &id2);
	if (SetThreadPriority(hilo2, THREAD_PRIORITY_HIGHEST) == false) {
		PERROR("SetThreadPriority");
		return 1;
	}

	//BUCLE DEL PADRE
	for (i = 0; i < reps; i++)
	{
		printf("0");
		fflush(stdout);
	}
	*/
	Sleep(4000); // Se debe esperar 30 segundos para finalizar el programa
	
	return 0;
}

//FUNCION TRATAR ARGUMENTOS
void tratarArg(int argc, char * argv[], int *velocidad, int *parto) {

int param1, param2;


if(argc != 3) {
	fprintf(stderr,"%s\n","USO: ./ranas VELOCIDAD VELOCIDAD_PARTO");
	exit(1);
}

param1 = atoi(argv[1]);
param2 = atoi(argv[2]);

if (param1 < 0 || param1 > 1000) {
	fprintf(stderr, "%s\n", "Ha introducido una velocidad incorrecta.\nPor favor, introduzca una velocidad ente 0 y 1000.");
	exit(1);
} *velocidad = param1;

if (param2 <= 0) {
	fprintf(stderr, "%s\n", "Ha introducido un tiempo de partos incorrecto.\nIntroduzca un tiempo mayor de 0.");
	exit(1);
} *parto = param2;

}


//FUNCION CARGAR LIBRERIA RANAS.DLL
int cargarRanas() {

	if(error(funciones.ranasDLL = LoadLibrary("ranas.dll") , "")) return 1;
	if(error(funciones.avanceRana = (BOOL(*)(int *,int *,int)) GetProcAddress(funciones.ranasDLL, "AvanceRana"), "AvanceRana")) return 1;
	if(error(funciones.avanceRanaFin = (BOOL(*)(int, int)) GetProcAddress(funciones.ranasDLL, "AvanceRanaFin"), "AvanceRanaFin")) return 1;
	if (error(funciones.avanceRanaIni = (BOOL(*)(int, int)) GetProcAddress(funciones.ranasDLL, "AvanceRanaIni"), "AvanceRanaIni")) return 1;
	if (error(funciones.avanceTroncos = (BOOL(*)(int i)) GetProcAddress(funciones.ranasDLL, "AvanceTroncos"), "AvanceTroncos")) return 1;
	if (error(funciones.comprobarEstadisticas = (BOOL(*)(LONG, LONG, LONG)) GetProcAddress(funciones.ranasDLL, "ComprobarEstadIsticas"), "ComprobarEstadisticas")) return 1;
	if (error(funciones.finRanas = (BOOL(*)(void)) GetProcAddress(funciones.ranasDLL, "FinRanas"), "FinRanas")) return 1;
	if (error(funciones.inicioRanas = (BOOL(*)(int, int*, int*, int*, int, TIPO_CRIAR)) GetProcAddress(funciones.ranasDLL, "InicioRanas"), "InicioRanas")) return 1;
	if (error(funciones.partoRanas = (BOOL(*)(int)) GetProcAddress(funciones.ranasDLL, "PartoRanas"), "PartoRanas")) return 1;
	
	/*
	Pausa1 = (void(*)(void)) GetProcAddress(ranasDLL, "Pausa");
	if (Pausa1 == NULL) {
		PERROR("Error en GetProcAddress: Pausa.");
		return -1;
	}*/

	if (error(funciones.puedoSaltar = (BOOL(*)(int, int, int)) GetProcAddress(funciones.ranasDLL, "PuedoSaltar"),"PuedoSaltar")) return 1;
	
	
	/*
	PrintMsg1 = (void(*)(char*)) GetProcAddress(ranasDLL, "PrintMsg");
	if (PrintMsg1 == NULL) {
		PERROR("Error enGetProcAddress: PrintMsg.");
		return -1;
	}*/

	return 0;
}

int error(BOOL ret, const char MSG_FUNCTION[]) {
	if (ret == FALSE) {
		fprintf(stderr,"%s: %s.\n",MSG_ERROR,MSG_FUNCTION);
		return 1;
	} else return 0;
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