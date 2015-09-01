#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <iostream>
using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn){ 
  colas.push_back(queue<int>());
  quantums.push_back(1); 
  for(size_t i = 1; i<argn.size(); i++){
    colas.push_back(queue<int>());
    quantums.push_back(argn[i]);
  }
}


void SchedNoMistery::load(int pid) {
  colas[0].push(pid);
}

void SchedNoMistery::unblock(int pid) {  
  colas[0].push(pid);
}




int SchedNoMistery::tick(int cpu, const enum Motivo m) {  
  
  int i = primera_cola_no_vacia();
  
  if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo 
    if(i == -1) return IDLE_TASK;
    else {
      time_left = quantums[i];
      cola_anterior = i;
			int sig = colas[i].front(); colas[i].pop(); 
			return sig;
		}
	} else if(m == BLOCK){
    if(i == -1) return current_pid(cpu);
    else { // esta bloqueado, no va a la cola
      time_left = quantums[i];
      cola_anterior = i;
 
	    int sig = colas[i].front(); colas[i].pop(); 
	  	return sig;
    } 
  } else {
    if(current_pid(cpu) != IDLE_TASK){
      time_left--;  
      if(time_left == 0){
        // Si el pid actual terminó, sigue el próximo    
        if(i == -1) return current_pid(cpu);
        else {
          if (cola_anterior+1 == colas.size()){
            colas[cola_anterior].push(current_pid(cpu));
          } else {
            colas[cola_anterior+1].push(current_pid(cpu));
          }

          time_left = quantums[i];
          cola_anterior = i;
          

	    	  int sig = colas[i].front(); colas[i].pop();
	    	  return sig;
        } 
      }
    }	
    if (current_pid(cpu) == IDLE_TASK && i != -1) { 	// Actual es IDLE
      time_left = quantums[i];
      cola_anterior = i;    
			

      int sig = colas[i].front(); colas[i].pop();
			return sig;
		} else {
			return current_pid(cpu);
		}
	}
}
