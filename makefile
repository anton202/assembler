assembler:	assembler.o utility.o hellper.o firstRun.o \
			machineInstruction.o symbolTable.o register.o data.o \
			instruction.o validAddressingModes.o externalSymbolTable.o 
			gcc -ansi -Wall -pedantic -o assembler assembler.o utility.o hellper.o firstRun.o \
			machineInstructions.o symbolTable.o data.o registers.o\
			instruction.o validAddressingModes.o externalSymbolTable.o -lm

assembler.o: assembler.c
			 gcc -ansi -Wall -pedantic -c assembler.c

utility.o:	./utility/utility.c ./utility/utility.h ./tables/symbolTable/symbolTable.h \
			./tables/tables.h ./hellper/hellper.h
			gcc -ansi -Wall -pedantic -c ./utility/utility.c

hellper.o:	./hellper/hellper.c ./hellper/hellper.h
			gcc -ansi -Wall -pedantic -c ./hellper/hellper.c

firstRun.o:	./firstRun/firstRun.c ./firstRun/firstRun.h ./tables/tables.h ./tables/symbolTable/symbolTable.h \
			./hellper/hellper.h ./machineCode/machineCode.h ./utility/utility.h
			gcc -ansi -Wall -pedantic -c ./firstRun/firstRun.c

machineInstruction.o:	./tables/machineInstructions.c ./tables/tables.h
						gcc -ansi -Wall -pedantic -c ./tables/machineInstructions.c

symbolTable.o:	./tables/symbolTable/symbolTable.c ./tables/symbolTable/symbolTable.h ./utility/utility.h
				gcc -ansi -Wall -pedantic -c ./tables/symbolTable/symbolTable.c

register.o:	./tables/registers.c
			gcc -ansi -Wall -pedantic -c ./tables/registers.c				

data.o:	./machineCode/data.c ./machineCode/machineCode.h ./utility/utility.h
		gcc -ansi -Wall -pedantic -c ./machineCode/data.c

instruction.o: ./machineCode/instruction.c ./machineCode/machineCode.h ./utility/utility.h
				gcc -ansi -Wall -pedantic -c ./machineCode/instruction.c

validAddressingModes.o:	./tables/validAddressingModes.c ./tables/tables.h
						gcc -ansi -Wall -pedantic -c ./tables/validAddressingModes.c

externalSymbolTable.o:	./tables/symbolTable/externalSymbolTable.c ./tables/symbolTable/symbolTable.h ./utility/utility.h
						gcc -ansi -Wall -pedantic -c ./tables/symbolTable/externalSymbolTable.c

clean:	
			rm assembler assembler.o utility.o hellper.o firstRun.o \
			machineInstructions.o symbolTable.o data.o registers.o\
			instruction.o validAddressingModes.o externalSymbolTable.o 

