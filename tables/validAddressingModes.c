#include <string.h>
#include "tables.h"
#include <stdio.h>

/* valide Addressing modes are: 0,1,2,3*/
/* -1 means no valid addressing modes */

AddressingModes validAdrressingModesTable[] = {
	{"mov", {0, 1, 3}, {1, 3}},
	{"cmp", {0, 1, 3}, {0, 1, 3}},
	{"add", {0, 1, 3}, {1, 3, -1}},
	{"sub", {0, 1, 3}, {1, 3, -1}},
	{"lea", {1, -1, -1}, {1, 3, -1}},
	{"clr", {-1, -1, -1}, {1, 3, -1}},
	{"not", {-1, -1, -1}, {1, 3, -1}},
	{"inc", {-1, -1, -1}, {1, 3, -1}},
	{"dec", {-1, -1, -1}, {1, 3, -1}},
	{"jmp", {-1, -1, -1}, {1, 2, -1}},
	{"bne", {-1, -1, -1}, {1, 2, -1}},
	{"jsr", {-1, -1, -1}, {1, 2, -1}},
	{"red", {-1, -1, -1}, {1, 3, -1}},
	{"prn", {-1, -1, -1}, {0, 1, 3}},
	{"rts", {-1, -1, -1}, {-1, -1, -1}},
	{"stop", {-1, -1, -1}, {-1, -1, -1}},

};

/*returns 0 if not vaild. returns 1 if valid*/
int isValidAddressingMode(char *operationName, int srcOrDestenationOp, int addressingMode)
{
	int i = 0;
	int k;
	for (; i < 16; i++)
	{
		if (strcmp(validAdrressingModesTable[i].operationName, operationName) == 0)
		{
			if (srcOrDestenationOp == 1)
			{
				for (k = 0; k < sizeof(validAdrressingModesTable[i].sourceOpeAddressingModes) / sizeof(validAdrressingModesTable[i].sourceOpeAddressingModes[0]); k++)
				{
					if (validAdrressingModesTable[i].sourceOpeAddressingModes[k] == addressingMode)
					{
						return 1;
					}
				}
			}
			else if (srcOrDestenationOp == 2)
			{
				for (k = 0; k < sizeof(validAdrressingModesTable[i].destinationOpAddressingModes) / sizeof(validAdrressingModesTable[i].destinationOpAddressingModes[0]); k++)
				{
					if (validAdrressingModesTable[i].destinationOpAddressingModes[k] == addressingMode)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}