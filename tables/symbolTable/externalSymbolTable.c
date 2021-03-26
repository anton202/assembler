#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ExternSymbol *externalSymbolTable = NULL;

/*implemented linked list*/
ExternSymbol *insertExternalSymbol(ExternSymbol *entry)
{
    ExternSymbol *symTable = externalSymbolTable;
    
        if (symTable == NULL)
        {
            externalSymbolTable = entry;
            return symTable;
        }
        else
        {
            while (symTable->next != NULL)
            {
                symTable = symTable->next;
            }

            symTable->next = entry;
            return symTable->next;
        }
    
    return NULL;
}


ExternSymbol *createExternalSymbol(char *symName, int value)
{

    ExternSymbol *newSymbol = (ExternSymbol *)malloc(sizeof(ExternSymbol));
    if (newSymbol == NULL)
    {
        printf("Error occured whlile allocating memory");
        exit(0);
    }
    newSymbol->next = NULL;
    newSymbol->name = symName;
    newSymbol->value = value;
    return newSymbol;
}