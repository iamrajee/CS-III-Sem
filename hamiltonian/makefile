CC = gcc
OBJS = main.o graph_lib.o hamiltonian.o

a.out : ${OBJS}
	${CC} ${OBJS}
hamiltonian.o: hamiltonian.c
	${CC} -c hamiltonian.c
main.o: main.c
	${CC} -c main.c
graph_lib.o : graph_lib.c
	${CC} -c graph_lib.c

clean:
	\rm a.out *.o *.dot

