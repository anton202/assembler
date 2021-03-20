typedef struct MachineInstructions
{
	char *instructionName;
	char opcFunct[8];
} MaInstruction;

typedef struct ValidAddressingMode
{
	char *operationName;
	char sourceOpeAddressingModes[3];
	char destinationOpAddressingModes[3];
} AddressingModes;

char *searchOpperation(char *opName);
int searchRegisterName(char *rName);
int isValidAddressingMode(char *operationName, int srcOrDestenationOp, int addressingMode);
