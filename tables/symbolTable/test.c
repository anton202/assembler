#include <stdio.h>
#include "symbolTable.h"

int main(void)
{

    Symbol *searchSym = NULL;
    Symbol *newSymbol = createSymbol("STR", 101, "code", '\0');
    Symbol *newSymbol2 = createSymbol("MAIN", 103, "code", '\0');
    Symbol *newSymbol3 = createSymbol("LOOP", 105, "code", '\0');
    Symbol *newSymbol4 = createSymbol("START", 107, "code", '\0');
    Symbol *newSymbol5 = createSymbol("STOP", 106, "code", '\0');

    if (newSymbol != NULL && newSymbol2 != NULL)
    {

        insertSymbol(newSymbol);
        insertSymbol(newSymbol2);
        insertSymbol(newSymbol3);
        insertSymbol(newSymbol4);
        insertSymbol(newSymbol5);
    }

    printHead();

    searchSym = searchSymbol("START");
    if (searchSym != NULL)
    {
        printf("symbol name: %s, value: %d", searchSym->symbol, searchSym->value);
    }
    return 1;
}