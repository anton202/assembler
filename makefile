all: assembler

assembler: main.o machineInstructions.o validAddressingModes.o
	gcc -ansi -Wall -pedantic -o assembler test.o ./tables/machineInstructions.o ./tables/validAddressingModes.o 
	
test.o: test.c
	gcc -ansi -Wall -pedantic -c test.c
	
pre.o: pre.c
	gcc -ansi -Wall -pedantic -c pre.c
	

