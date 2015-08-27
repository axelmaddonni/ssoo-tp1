#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
  for(int i = 0; i<argn[0]; i++){
    quantums.push_back(argn[i+1]);
    time_left.push_back(argn[i+1]);
  }
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
  q.push(pid);
}

void SchedRR::unblock(int pid) {
}

int SchedRR::tick(int cpu, const enum Motivo m) { 
  if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo
		if (q.empty()){
     
      return IDLE_TASK;
    }
    else {
      time_left[cpu] = quantums[cpu];
			int sig = q.front(); q.pop(); 
			return sig;
		}
	} else if(m == BLOCK){
    if(!q.empty()){
      q.push(current_pid(cpu));
      time_left[cpu] = quantums[cpu];
	  	int sig = q.front(); q.pop(); 
	  	return sig;
    }
    return current_pid(cpu);
  } else {
    if(current_pid(cpu) != IDLE_TASK){
      time_left[cpu]--;  
      if(time_left[cpu] == 0){
        // Si el pid actual terminó, sigue el próximo    
        if(!q.empty()){
          q.push(current_pid(cpu));
          time_left[cpu] = quantums[cpu];
	    	  int sig = q.front(); q.pop();
	    	  return sig;
        }

        return current_pid(cpu);
      }
    }
		// Siempre sigue el pid actual mientras no termine.
	  if (current_pid(cpu) == IDLE_TASK && !q.empty()) {
			int sig = q.front(); q.pop();
			return sig;
		} else {
			return current_pid(cpu);
		}
	}
}

