#include "tasks.h"
#include <stdlib.h>
#include <iostream>


using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params) { // params: n, bmin, bmax
  srand(10);

  int n = params[0];
  int bmin = params[1];
  int bmax = params[2];

  for(int i = 0; i < n; i++){
    double r = rand();
    r /= RAND_MAX;
    r *= (bmax-bmin);
    r += bmin;
    uso_IO(pid, (int) r);
  }
}

void TaskBatch(int pid, vector<int> params) { // params: total_cpu, cant_bloqueos

  int total_cpu = params[0];
  int cant_bloqueos = params[1]; 

  std::vector<int> tiempos_de_bloqueo;
  for(int i = 0; i<total_cpu; i++){
    tiempos_de_bloqueo.push_back(i); // armo el vector de tiempos de bloqueo
  }                                 // = {0, 1, 2, 3, 4, ..., total_cpu-1}

  // Uso fisher yates para mezclarlo
  // https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
  int n = tiempos_de_bloqueo.size();
  for(int i = n-1; i>=1; i--){
    int j = rand()%(n-i) + i; //j al azar,  i<=j<n
    
    int temp = tiempos_de_bloqueo[i];
    tiempos_de_bloqueo[i] = tiempos_de_bloqueo[j];
    tiempos_de_bloqueo[j] = temp;
  }


  for(int i = 0; i<total_cpu; i++){
    // me fijo si toca bloquear o toca usar cpu
    // si esta en las primeras cant_bloqueos posiciones
    // de tiempos_de_bloqueo toca bloquear
    bool hay_que_bloquear = false;
    for(int j = 0; j<cant_bloqueos; j++){
      if(tiempos_de_bloqueo[j] == i){
        hay_que_bloquear = true;
        break;
      }
    }

    if(hay_que_bloquear) uso_IO(pid, 1);
    else uso_CPU(pid, 1);
  }
}


void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
}
