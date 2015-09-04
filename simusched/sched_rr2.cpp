#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
  int cores = argn[0];
  colas = std::vector<std::queue<int> >(cores, std::queue<int>());
  procesos_totales = std::vector<int>(cores, 0);
  for(int i = 0; i < cores; i++){
    quantums.push_back(argn[i+1]);
    time_left.push_back(argn[i+1]);
  }
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
  int min_procesos_totales = 0;
  for(int i = 0; i<procesos_totales.size(); i++){
    if(procesos_totales[i] < min_procesos_totales){
      min_procesos_totales = i;
    }
  }

  colas[min_procesos_totales].push(pid);
  procesos_totales[min_procesos_totales]++;

}

void SchedRR2::unblock(int pid) {
  colas[bloqueados[pid]].push(pid);
  bloqueados.erase(pid);
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
  if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo
    procesos_totales[cpu]--;
		if (colas[cpu].empty()) return IDLE_TASK;
    else {
      time_left[cpu] = quantums[cpu];
			int sig = colas[cpu].front(); colas[cpu].pop(); 
			return sig;
		}
	} else if(m == BLOCK){
    bloqueados[current_pid(cpu)] = cpu;  // me acuerdo de que cpu lo saque 
    
    if(!colas[cpu].empty()){ // esta bloqueado, no va a la cola
      time_left[cpu] = quantums[cpu];
	  	int sig = colas[cpu].front(); colas[cpu].pop(); 
	  	return sig;
    }

    return current_pid(cpu);
  } else {
    if(current_pid(cpu) != IDLE_TASK){
      time_left[cpu]--;  
      if(time_left[cpu] == 0){
        // Si el pid actual terminó, sigue el próximo    
        if(!colas[cpu].empty()){
          colas[cpu].push(current_pid(cpu));
          time_left[cpu] = quantums[cpu];
	    	  int sig = colas[cpu].front(); colas[cpu].pop();
	    	  return sig;
        }

        return current_pid(cpu);
      }
    }	
	  if (current_pid(cpu) == IDLE_TASK && !colas[cpu].empty()) {
			int sig = colas[cpu].front(); colas[cpu].pop();
			return sig;
		} else {
			return current_pid(cpu);
		}
	}
}
