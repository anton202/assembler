#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../tables/tables.h"
#include "../tables/symbolTable/symbolTable.h"

#define MAX_SYMBOL_LENGTH 31

char *isSymbol(char *line, int *lineIndex)
{
    int c, i = 0;
    int k = 0;
    int j = 0;
    char *symbol;

    /*skip white space*/
    while (isspace(*(line + k)))
    {
        k++;
    }

    while ((c = *(line + k)) != ' ' && c != ':')
    {
        i++;
        k++;
    }

    if (c != ':')
    {
        return NULL;
    }

    i -= 1;
    k -= 1;
    symbol = (char *)malloc(i + 1);

    if (symbol != NULL)
    {
        k -= i;
        while ((c = *(line + k)) != ':')
        {
            *(symbol + j) = c;
            j++;
            k++;
        }
        *(symbol + j) = '\0';
        *lineIndex = k + 1;
    }
    else
    {
        exit(0);
    }
    return symbol;
}

int isSymbolValid(char *symbol, int lineNumber)
{
    if (strlen(symbol) > MAX_SYMBOL_LENGTH)
    {
        printf("\n line number: %d :Error: symbol name must be less than 31 characters.", lineNumber);
        free(symbol);
        return 0;
    }
    if (isdigit(symbol))
    {
        printf("\nline number: %d Error: symbol name can`t begin with a digit.", lineNumber);
        free(symbol);
        return 0;
    }
    if (searchOpperation(symbol) != NULL)
    {
        printf("\nline number: %d Error: symbol name can`t be assembly operation name.", lineNumber);
        free(symbol);
        return 0;
    }
    if (searchSymbol(symbol) != NULL)
    {
        printf("line number: %d Error: symbol name already defined.", lineNumber);
        free(symbol);
        return 0;
    }

    if (searchRegisterName(symbol))
    {
        printf("line number: %d Error: symbol name can`t be saved register name", lineNumber);
    }
    return 1;
    /*check if symbol is not register name*/
}