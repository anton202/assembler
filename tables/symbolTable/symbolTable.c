#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Symbol *symbolTabel = NULL;

/*implemented linked list*/
Symbol *insertSymbol(Symbol *entry)
{
    Symbol *symTable = symbolTabel;
    if (searchSymbol(entry->symbol) == NULL)
    {
        if (symTable == NULL)
        {
            symbolTabel = entry;
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
    }
    return NULL;
}

/*Lineara search over linked list*/
Symbol *searchSymbol(char *symbolName)
{
    Symbol *symTable = symbolTabel;
    while (symTable != NULL)
    {
        if (!strcmp(symTable->symbol, symbolName))
        {
            return symTable;
        }
        symTable = symTable->next;
    }
    
    return NULL;
}

/*if atr2 is missing enter '\0'*/
Symbol *createSymbol(char *symName, int value, char *atr1, char *atr2)
{

    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    if (newSymbol != NULL)
    {
        newSymbol->next = NULL;
        newSymbol->symbol = symName;
        newSymbol->value = value;
        newSymbol->attributes[0] = atr1;
        newSymbol->attributes[1] = atr2;
        return newSymbol;
    }
    return NULL;
}

void printHead()
{
    printf("symbol name at head:%s, value: %d \n", symbolTabel->symbol,symbolTabel->value);
}

int checkIfExternalAtribute(Symbol *externSymbol)
{
    Symbol *sym = searchSymbol(externSymbol->symbol);
    int i = 0;

    if (sym != NULL)
    {
        for (; i < 3; i++)
        {
            if (!strcmp(sym->attributes[i], "external"))
            {
                return 1;
            }
        }
    }
    return 0;
}