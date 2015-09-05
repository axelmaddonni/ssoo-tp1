#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include <map>
#include "basesched.h"

class SchedNoMistery : public SchedBase {
  public:
    SchedNoMistery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);  
  private:
    std::vector<std::queue<int> > colas;
    std::vector<int> quantums;
    int time_left;
    mutable int cola_anterior;

    std::map<int, int> bloqueados; // para cada bloqueado, me guardo en que cola estaba


    int primera_cola_no_vacia(){
      for(int i = 0; i<colas.size(); i++){
        if(!colas[i].empty()) return i;
      }
      return -1;
    }

};

#endif
