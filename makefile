TP1: main.o usocomun.o stepA.o stepB.o stepC.o stepD.o
	gcc -o TP1 main.o stepA.o stepB.o stepC.o stepD.o usocomun.o
main.o: main.c stepA.h stepB.h stepC.h stepD.h usocomun.h
	gcc -c main.c
stepA.o: stepA.c usocomun.h stepA.h
	gcc -c stepA.c
stepB.o: stepB.c usocomun.h stepB.h
	gcc -c stepB.c
stepC.o: stepC.c usocomun.h stepC.h
	gcc -c stepC.c
stepD.o: stepD.c usocomun.h stepD.h
	gcc -c stepD.c
usocomun.o: usocomun.c usocomun.h
	gcc -c usocomun.c 
clean:
	rm -f TP1 *.o