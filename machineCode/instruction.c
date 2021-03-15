#include <stdio.h>
#include <stdlib.h>
#include "machineCode.h"
#define MEMORY_START_LOCATION 100

static int IC = MEMORY_START_LOCATION;
static int i = 0;
static Instruction *instructionTable[MEMORY_SIZE];


int getInstructionCount(void)
{
    return IC;
}

Instruction *createInstruction(char *instruction,int memoryLocation, int length, char ARE)
{
    Instruction *inst = NULL;
    inst = (Instruction*)malloc(sizeof(Instruction));

    if(inst == NULL){
        printf("Error: error ocured while allocating memorey for instruction");
        exit(0);
    }

    inst->instruction = instruction;
    inst->memoryLocation = memoryLocation;
    inst->instructionLength = length;
    inst->ARE = ARE;

    return inst;
}

int addInstructionToInstructionTable(Instruction *inst)
{
    if(i < MEMORY_SIZE && (i + getDataCount()) < MEMORY_SIZE)
    {
        instructionTable[i] = inst;
        i++;
        IC++;
        return 1;
    }

    printf("Error: not enough memory space");
    return 0;
}