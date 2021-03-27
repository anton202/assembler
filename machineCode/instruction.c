#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
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
    i++;
}

void resetInstructionCount(void)
{
    i = 0;
    IC = MEMORY_START_LOCATION;
    secondRunCounter = 0;
}

void printInstructionTable(void)
{
    int c = 0;
    int k = 0;
    for (; c < i; c++)
    {
        printf("\nMemory loation: %d binary code: ", instructionTable[c]->memoryLocation);
        for (k = 0; k < 12; k++)
        {
            printf("%d ", instructionTable[c]->instruction[k]);
        }
        printf(" %c", instructionTable[c]->ARE);

        putchar('\n');
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

void saveInstructionAtSpecificPlace(char *instruction, int position, int memoryLocation, int length, char ARE)
{
    instructionTable[position] = createInstruction(instruction, memoryLocation, length, ARE);
}

void resetInstructionTabale(void)
{
    int j = 0;
    for (; j < i; j++)
    {

        free(instructionTable[j]);
    }

    resetInstructionCount();
}

void createObjectFile(char *fileName)
{
    Data *node = getDataHead();
    int k = 0;
    FILE *fp;
    char *instruction;
    char ARE;
    int memoryLocation;

    fp = fopen(addExtentitonToFileName(fileName,".ob"), "w");
    fprintf(fp,"\t%d %d\n",i,getDataCount());

    for (; k < i; k++)
    {
        instruction = instructionTable[k]->instruction;
        memoryLocation = instructionTable[k]->memoryLocation;
        ARE = instructionTable[k]->ARE;

        fprintf(fp,"0%d %s %c\n",memoryLocation,converBinaryToHex(instruction),ARE);
    }

    while (node != NULL)
    {
        fprintf(fp,"0%d %s %c\n",node->memoryLocatin,converBinaryToHex(node->data),node->ARE);
        node = node->next;
    }
    
    fclose(fp);
}