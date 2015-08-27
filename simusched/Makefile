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

ejercicio2: simusched rolando.tsk graphsched.py
	./simusched rolando.tsk 1 4 1 SchedFCFS | ./graphsched.py > ej2-1core.png
	./simusched rolando.tsk 2 4 1 SchedFCFS | ./graphsched.py > ej2-2core.png


ejercicio4: simusched


ejercicio5: simusched LoteEj5.tsk graphsched.py
	./simusched LoteEj5.tsk 1 2 1 SchedRR 2 | ./graphsched.py > ej5-q2.png	
	./simusched LoteEj5.tsk 1 2 1 SchedRR 10 | ./graphsched.py > ej5-q10.png	
	./simusched LoteEj5.tsk 1 2 1 SchedRR 50 | ./graphsched.py > ej5-q50.png	


ejercicio6: simusched LoteEj5.tsk graphsched.py
	./simusched LoteEj5.tsk 1 2 1 SchedFCFS | ./graphsched.py > ej6.png

new: clean all

