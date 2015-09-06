export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS) sched_mistery.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	rm -f $(OBJS) $(MAIN)


ejercicio1: simusched
	./simusched LoteEj1.tsk 1 2 1 SchedFCFS | ./graphsched.py > ej1.png

ejercicio2: simusched rolando.tsk graphsched.py
	./simusched rolando.tsk 1 4 1 SchedFCFS | ./graphsched.py > ej2-1core.png
	./simusched rolando.tsk 2 4 1 SchedFCFS | ./graphsched.py > ej2-2core.png

ejercicio3: simusched
	./simusched LoteEj3.tsk 1 4 1 SchedFCFS | ./graphsched.py > ej3.png

ejercicio4: simusched


ejercicio5: simusched LoteEj5.tsk graphsched.py
	./simusched LoteEj5.tsk 1 2 1 SchedRR 2 | ./graphsched.py > ej5-q2.png	
	./simusched LoteEj5.tsk 1 2 1 SchedRR 10 | ./graphsched.py > ej5-q10.png	
	./simusched LoteEj5.tsk 1 2 1 SchedRR 50 | ./graphsched.py > ej5-q50.png	


ejercicio6: simusched LoteEj5.tsk graphsched.py
	./simusched LoteEj5.tsk 1 2 1 SchedFCFS | ./graphsched.py > ej6.png

ejercicio7: simusched LoteEj71.tsk LoteEj72.tsk graphsched.py
	./simusched LoteEj71.tsk 1 2 1 SchedMistery 2 3 4 | ./graphsched.py > ej7-1.png
	./simusched LoteEj72.tsk 1 1 1 SchedMistery 2 5 10 20 | ./graphsched.py > ej7-2.png



ejercicio8:
	./simusched LoteEj81.tsk 2 1 6 SchedRR 5 5 | ./graphsched.py > ej8-1rr.png
	./simusched LoteEj81.tsk 2 1 6 SchedRR2 5 5 | ./graphsched.py > ej8-1rr2.png
	./simusched LoteEj82.tsk 2 1 2 SchedRR 5 5 | ./graphsched.py > ej8-2rr.png
	./simusched LoteEj82.tsk 2 1 2 SchedRR2 5 5 | ./graphsched.py > ej8-2rr2.png



new: clean all

