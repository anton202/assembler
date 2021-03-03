#include "tables.h"

/* valide Addressing modes are: 0,1,2,3*/
/* -1 means no valid addressing modes */


AddressingModes validAdrressingModesTable[] = {
	{
		"mov",{0,1,3},{1,3}
	},
	{
		"cmp",{0,1,3},{0,1,3}
	},
	{
		"add",{0,1,3},{1,3}
	},
	{
		"sub",{0,1,3},{1,3}
	},
	{
		"lea",{1},{1,3}
	},
	{
		"clr",{-1},{1,3}
	},
	{
		"not",{-1},{1,3}
	},
	{
		"inc",{-1},{1,3}
	},
	{
		"dec",{-1},{1,3}
	},
	{
		"jmp",{-1},{1,2}
	},
	{
		"bne",{-1},{1,2}
	},
	{
		"jsr",{-1},{1,2}
	},
	{
		"red",{-1},{1,3}
	},
	{
		"prn",{-1},{0,1,3}
	},
	{
		"rts",{-1},{-1}
	},
	{
		"stop" ,{-1},{-1}
	},

};
