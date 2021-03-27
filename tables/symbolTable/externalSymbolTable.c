#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "../../utility/utility.h"

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

void resetExternalSymbolTable(void)
{
    cleantExternalSymbolPointer(externalSymbolTable);
    externalSymbolTable = NULL;
}

void cleantExternalSymbolPointer(ExternSymbol *node)
{
    if (node != NULL)
    {
        if (node->next != NULL)
        {
            cleantExternalSymbolPointer(node->next);
        }

        free(node);
    }
}

void createExtFile(char *fileName)
{
    ExternSymbol *node = externalSymbolTable;
    FILE *fp = NULL;

    if (node != NULL)
    {
        fp = fopen(addExtentitonToFileName(fileName, ".ext"), "w");
    }
    while (node != NULL)
    {
        fprintf(fp, "%s 0%d\n", node->name, node->value);
        node = node->next;
    }

    if (fp != NULL)
    {
        fclose(fp);
    }
}