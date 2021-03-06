#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "../../utility/utility.h"

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
    if (newSymbol == NULL)
    {
        printf("Error occured whlile allocating memory");
        exit(0);
    }
    newSymbol->next = NULL;
    newSymbol->symbol = symName;
    newSymbol->value = value;
    newSymbol->attributes[0] = atr1;
    newSymbol->attributes[1] = atr2;
    return newSymbol;
}

void printHead()
{
    printf("symbol name at head:%s, value: %d \n", symbolTabel->symbol, symbolTabel->value);
}

void printSymbolTable(void)
{
    Symbol *node = symbolTabel;

    while (node != NULL)
    {
        printf("\nsymbol name :%s, value: %d \n", node->symbol, node->value);
        node = node->next;
    }
}

void changeSymbolMemoryLocation(int newMemoryLocation)
{
    Symbol *node = symbolTabel;
    while (node != NULL)
    {
        if (!strcmp(node->attributes[0], "data") || !strcmp(node->attributes[0], "data"))
        {
            node->value = node->value + newMemoryLocation;
        }
        node = node->next;
    }
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

void resetSymbolTable(void)
{
    cleanSymbolPointer(symbolTabel);
    symbolTabel = NULL;
}

void cleanSymbolPointer(Symbol *node)
{
    if (node->next != NULL)
    {
        cleanSymbolPointer(node->next);
    }
    if (node != NULL)
    {
        free(node);
    }
}

void createEntFile(char *fileName)
{
    Symbol *node = symbolTabel;
    FILE *fp = NULL;

    while (node != NULL)
    {

        if (!strcmp(node->attributes[1], "entry"))
        {
            if (fp == NULL)
            {
                fp = fopen(addExtentitonToFileName(fileName, ".ent"), "w");
            }
            fprintf(fp, "%s 0%d\n", node->symbol, node->value);
        }
        node = node->next;
    }
    if (fp != NULL)
    {
        fclose(fp);
    }
}