TP1: build/main.o build/usocomun.o build/stepA.o build/stepB.o build/stepC.o build/stepD.o
	gcc build/main.o build/usocomun.o build/stepA.o build/stepB.o build/stepC.o build/stepD.o -o TP1
build/main.o: 
	gcc -c -Iinc src/main.c -o build/main.o
build/usocomun.o: 
	gcc -c -Iinc src/usocomun.c -o build/usocomun.o
build/stepA.o: 
	gcc -c -Iinc src/stepA.c -o build/stepA.o
build/stepB.o:
	gcc -c -Iinc src/stepB.c -o build/stepB.o
build/stepC.o: 
	gcc -c -Iinc src/stepC.c -o build/stepC.o
build/stepD.o: 
	gcc -c -Iinc src/stepD.c -o build/stepD.o
clean:
	rm -f TP1 *.o