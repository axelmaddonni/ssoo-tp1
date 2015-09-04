#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include <map>
#include "basesched.h"

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
  private:
    std::vector<std::queue<int> > colas;
    std::vector<int> procesos_totales;
    std::vector<int> quantums;
    std::vector<int> time_left;

    std::map<int, int> bloqueados; // diccionario. clave = pid, significado = core
};

#endif
