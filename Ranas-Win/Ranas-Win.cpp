#include <stdio.h> 
#include <stdlib.h>
#include <Windows.h>
#include "ranas.h"

int main(int argc, char * argv[])
{
	HANDLE hilo1, hilo2;
	CHAR char1, char2;
	DWORD id1, id2;
	INT i, reps;

	//TRATAMIENTO ARGUMENTOS
	//...

	// He puesto un comentario

	//PRIORIDAD DEL PROCESO NORMAL --> IDLE
	if (SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS) == false) {
		perror("SetPriorityClass");
		return 1;
	}

	//CREACIÓN HILO 1
	hilo1 = CreateThread(NULL, 0, funcion_hilo1, (void*)reps, NULL, &id1);
	if (SetThreadPriority(hilo1, THREAD_PRIORITY_HIGHEST) == false) {
		perror("SetThreadPriority");
		return 1;
	}

	//CREACIÓN HILO 2
	hilo2 = CreateThread(NULL, 0, funcion_hilo1, (void*)reps, NULL, &id2);
	if (SetThreadPriority(hilo2, THREAD_PRIORITY_HIGHEST) == false) {
		perror("SetThreadPriority");
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
	return 0;
}


//FUNCION DEL HILO 1
DWORD WINAPI funcionHilo1(LPVOID argumento) {
	INT i, reps;
	//...
}


//FUNCION DEL HILO 2
DWORD WINAPI funcionHilo2(LPVOID argumento) {
	INT i, reps;
	//...
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
