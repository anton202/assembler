typedef struct MachineInstructions{
	char *instructionName;
	char opcFunct[8];
}MaInstruction;

typedef struct ValidAddressingMode{
	char *operationName;
	char sourceOpeAddressingModes[3];
	char destinationOpAddressingMModes[3];
}AddressingModes;


char *searchOpperation(char *opName);

int searchRegisterName(char *rName);