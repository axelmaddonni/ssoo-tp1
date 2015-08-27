#include "tasks.h"
#include <stdlib.h>

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

 // aordate de exit
  /*
  std::vector<int> momentos_io;
  while(momentos_io.size() < cant_bloqueos){
  while(cant_bloqueos>0 && cant_bloqueos+1<=total_cpu){   
    int r = rand();
    if(r%2 == 0){
      uso_IO(pid, 1);
      cant_bloqueos--;
      total_cpu--;
    } else {
      uso_CPU(pid, 1);
      total_cpu--;
    }
  }

  if(cant_bloqueos>0){
    for(int i = 0; i<cant_bloqueos; i++){
      uso_IO(pid, 1);
      total_cpu--;
    }
  } 

  while(total_cpu>1){ // llamada a exit()
    uso_CPU(pid, 1);

}
*/


}


void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
}
