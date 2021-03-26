#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "firstRun.h"
#include "../hellper/hellper.h"
#include "../utility/utility.h"
#include "../tables/tables.h"
#include "../machineCode/machineCode.h"
#include "../tables/symbolTable/symbolTable.h"

int firstRun(char *line, int lineNumber);

int main(int argc, char *argv[])
{
    char line[80];
    FILE *fp;
    int lineNumber = 1;
    int error = 0;
    int i = 1;
    int DCF, ICF;

    if (argc == 1)
    {
        printf("\nError: Please enter file name\n");
        return 0;
    }

    if (checkFiles(argc, argv) == -1)
    {
        return 0;
    }

    fp = fopen(addExtentitonToFileName(argv[1]), "r");

    for (; i < argc; i++)
    {
        fp = fopen(addExtentitonToFileName(argv[i]), "r");

        while (readLine(line, fp, lineNumber) != EOF)
        {
            if (!firstRun(line, lineNumber))
            {
                error = 1;
            }
            lineNumber++;
        }
        if (error)
        {
            return 0;
        }

        ICF = getInstructionCount();
        DCF = getDataCount();

        changeSymbolMemoryLocation(ICF);
        changeMemoryLocation(ICF);
        /*Second run starts here*/
        lineNumber = 1;
        error = 0;

       fseek(fp, 0, SEEK_SET);
       while (readLine(line, fp, lineNumber) != EOF)
        {
            if (!secondRun(line, lineNumber))
            {
                error = 1;
            }
            lineNumber++;
        }
        fclose(fp);
    }

    /*
        create output files
    */
    printInstructionTable();
   /* printf("Data table: \n");*/
    printDataTable();
    printSymbolTable();
    return 1;
}

int firstRun(char *line, int lineNumber)
{
    int lineIndex = 0;
    int isDataDirective;
    Operands *operands;
    int symbolDecleration = 0;
    char *symbol, *operationName;

    if (commentLine(line) || emptyLine(line, &lineIndex))
    {
        return 1;
    }

    symbol = isSymbol(line, &lineIndex);
    if (symbol != NULL)
    {
        symbolDecleration = 1;
    }

    isDataDirective = checkIfDataDirective(line, &lineIndex);

    if (!isDataDirective || isDataDirective == 1)
    {
        if (symbolDecleration)
        {
            if (!isSymbolValid(symbol, 1) && isRegisterName(symbol, 1) && isSymbolDefined(symbol, 1))
            {
                return 0;
            }
            else
            {
                insertSymbol(createSymbol(symbol, getDataCount(), "data", '\0'));
            }
        }
    }

    if (!isDataDirective)
    {
        return readAndSaveDataDirective_Data(line, &lineIndex, lineNumber);
    }
    else if (isDataDirective == 1)
    {
        return readAndSaveStringDirective_data(line, &lineIndex, lineNumber);
    }
    else if (isDataDirective == 2)
    {
        return readAndSaveExternalSymbol(line, &lineIndex, lineNumber);
    }
    else if (isDataDirective == 3)
    {
        return 1;
    }

    /* so if no .data, .string, .extern, .entry then it is an instruction line*/

    if (symbolDecleration)
    {
        if (!saveInstructionLineSymbol(symbol, lineNumber))
        {
            return 0;
        }
    }

    /*get operation name and check if valid*/
    operationName = getOperationName(line, &lineIndex);
    if (searchOpperation(operationName) == NULL)
    {
        printf("\nline number: %d Error: operation %s is iligal operation.\n", lineNumber, operationName);
        return 0;
    }

    if (strcmp("rts", operationName) != 0 && strcmp("stop", operationName) && *(line + lineIndex) != ' ')
    {
        printf("line number: %d Error: There must be at least one space betwen an operation name and the first argument", lineNumber);
        return 0;
    }

    while (isspace(*(line + lineIndex)))
    {
        lineIndex++;
    }

    operands = readAndCodeOperands(operationName, line, &lineIndex, lineNumber);

    if (operands == NULL)
    {
        return 0;
    }

    saveFirstWord(createFirstWord(operationName, operands), operands);
    saveAdditionalWord(operands->sourceOpAddresingMode, operands->sourceOpBinaryCode);
    saveAdditionalWord(operands->destenationOpAddressongMode, operands->destenationOpBinaryCode);

    return 1;
}

int secondRun(char *line, int lineNumber)
{
    int lineIndex = 0;
    int whichDirective;

     if (commentLine(line) || emptyLine(line, &lineIndex))
    {
        return 1;
    }

    /*skips symbol declaration*/
    isSymbol(line, &lineIndex);
    whichDirective = checkIfDataDirective(line, &lineIndex);

    if (!whichDirective || whichDirective == 1 || whichDirective == 2)
    {
        return 1;
    }
    else if (whichDirective == 3)
    {
        return readAndSaveEntryDirectiveSymbol(line, &lineIndex, lineNumber);
    }

    return readAndCodeSymbolOperands(line, &lineIndex, lineNumber);
}