#include <string.h>
#include "tables.h"
#define tableSize 16

static MaInstruction machineInstructionsTable[tableSize] = {

	{"mov", {0, 0, 0, 0, 0, 0, 0, 0}},
	{"cmp", {0, 0, 0, 1, 0, 0, 0, 0}},
	{"add", {0, 0, 1, 0, 1, 0, 1, 0}},
	{"sub", {0, 0, 1, 0, 1, 0, 1, 1}},
	{"lea", {0, 1, 0, 0, 0, 0, 0, 0}},
	{"clr", {0, 1, 0, 1, 1, 0, 1, 0}},
	{"not", {0, 1, 0, 1, 1, 0, 1, 1}},
	{"inc", {0, 1, 0, 1, 1, 1, 0, 0}},
	{"dec", {0, 1, 0, 1, 1, 1, 0, 1}},
	{"jmp", {1, 0, 0, 1, 1, 0, 1, 0}},
	{"bne", {1, 0, 0, 1, 1, 0, 1, 1}},
	{"jsr", {1, 0, 0, 1, 1, 1, 0, 0}},
	{"red", {1, 1, 0, 0, 0, 0, 0, 0}},
	{"prn", {1, 1, 0, 1, 0, 0, 0, 0}},
	{"rts", {1, 1, 1, 0, 0, 0, 0, 0}},
	{"stop", {1, 1, 1, 1, 0, 0, 0, 0}}};

/*
searches if the given operation name exist in table
return: NULL if operation not found else returns operation name 
*/
char *searchOpperation(char *opName)
{
	int i;
	for (i = 0; i < tableSize; i++)
	{
		if (!strcmp(machineInstructionsTable[i].instructionName, opName))
		{
			return machineInstructionsTable[i].opcFunct;
		}
	}
	return NULL;
}
