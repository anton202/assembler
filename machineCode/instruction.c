#include <stdio.h>
#include <stdlib.h>
#include "machineCode.h"
#define MEMORY_START_LOCATION 100

static int IC = MEMORY_START_LOCATION;
static int i = 0;
static int secondRunCounter = 0;
static Instruction *instructionTable[MEMORY_SIZE];

int getInstructionCount(void)
{
    return IC;
}

void incInstructionCount(void)
{
    IC++;
}

void printInstructionTable(void)
{
    int c = 0;
    for (; c < i; c++)
    {
        printf("\nMemory loation: %d\n", instructionTable[c]->memoryLocation);
    }
}

int getSecondRoundCounter(void)
{
    return secondRunCounter;
}

Instruction *getInstruction(int position)
{
    return instructionTable[position];
}

void increamentSecounRoundCounter(int inc)
{
    secondRunCounter += inc;
}

Instruction *createInstruction(char *instruction, int memoryLocation, int length, char ARE)
{

    Instruction *inst = NULL;
    inst = (Instruction *)malloc(sizeof(Instruction));

    if (inst == NULL)
    {
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
    if ((i + getDataCount()) < MEMORY_SIZE)
    {
        instructionTable[i] = inst;
        i++;
        IC++;
        return 1;
    }
    printf("Error: not enough memory space, used memory: %d", i + getDataCount());
    return 0;
}

char *getInstructionsBinaryCode(int memoryPos)
{
    int j;
    for (j = 0; j < i; j++)
    {
        if (instructionTable[j]->memoryLocation == memoryPos)
        {
            return instructionTable[j]->instruction;
        }
    }
    return NULL;
}

void saveInstructionAtSpecificPlace(char *instruction, int position, int memoryLocation, int length, char ARE)
{
    instructionTable[position] = createInstruction(instruction, memoryLocation, length, ARE);
}