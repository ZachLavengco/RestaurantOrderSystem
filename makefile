Project4: program1.o program2.o program3.o
	gcc -o Project4 program1.o program2.o program3.o

program1.o: program1.c program.h
	gcc -c program1.c

program2.o: program2.c program.h
	gcc -c program2.c

program3.o: program3.c program.h
	gcc -c program3.c

clean:
	rm program1.o program2.o program3.o Project4