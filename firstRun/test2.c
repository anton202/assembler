#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "firstRun.h"
#include "../hellper/hellper.h"
#include "../utility/utility.h"
#include "../tables/tables.h"
#include "../machineCode/machineCode.h"
#include "../tables/symbolTable/symbolTable.h"

int main(int argc, char *argv[])
{
    int i = 0;
    char line[80];
    FILE *fp;
    int lineReadStatus;
    char *symbol, *operationName;
    int symbolDecleration = 0;
    int lineIndex = 0;
    int isDataDirective, lineNumber = 1;
    Operands *operands;

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
    lineReadStatus = readLine(line, fp, 1);

    symbol = isSymbol(line, &lineIndex);
    if (symbol != NULL)
    {
        printf("the symbol is: %s \n", symbol);
        if (isSymbolValid(symbol, 1) && !isRegisterName(symbol, 1) && !isSymbolDefined(symbol, 1))
            symbolDecleration = 1;
    }
    printf("\nline index: %d\n", lineIndex);

    isDataDirective = checkIfDataDirective(line, &lineIndex);
    if (!isDataDirective)
    {
        readAndSaveDataDirective_Data(line, &lineIndex);
    }
    else if (isDataDirective == 1)
    {
        readAndSaveStringDirective_data(line, &lineIndex, &lineNumber);
    }
    else if (isDataDirective == 2)
    {
        readAndSaveExternalSymbol(line, &lineIndex, lineNumber);
    }
    else if (isDataDirective == 3)
    {
        /* return to the begining of the run. this will be delt with in the second run*/
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
        printf("\n number line: %d Error: operation %s is iligal operation.\n", 1, operationName);
        return 0;
    }
    printf("operation name is: %s\n", operationName);

    /*check if at least on space and nothing else is between operation anem and the opperand*/
    /*also notice that there are two operation names that do not have operands*/

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

    printInstructionTable();

    /* printf("\nSaved data:\n");
    printf("source operand addressong mode: %d\n", operands->sourceOpAddresingMode);
    printf("source operand Binary Code mode: %s", operands->sourceOpBinaryCode);
    for (; i < 12; i++)
    {
        printf("%d ",operands->sourceOpBinaryCode[i]);
    }
    
    printf("\ndestenation operand Addressong Mode: %d\n", operands->destenationOpAddressongMode);
    printf("destenation operand binary code: %s", operands->destenationOpBinaryCode);
    for (i = 0; i < 12; i++)
    {
        printf("%d ",operands->destenationOpBinaryCode[i]);
    }*/

    return 1;
}
