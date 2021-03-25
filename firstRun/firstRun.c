#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../tables/tables.h"
#include "../tables/symbolTable/symbolTable.h"
#include "../hellper/hellper.h"
#include "../machineCode/machineCode.h"
#include "../utility/utility.h"
#include "firstRun.h"

#define MAX_NUMBER 2047
#define MIN_NUMBER -2047
#define NUMBER_LENGTH 4
#define MAX_SYMBOL_LENGTH 31
#define MAX_STRING_LENGTH 70



int commentLine(char *line)
{
    if(*line == ';')
    {
        return 1;
    }
    return 0;
}

int emptyLine(char *line, int *lineIndex)
{
    while (isspace(*(line + *lineIndex)))
    {
        *lineIndex += 1;
    }
    if(*(line + *lineIndex) == '\0')
    {
        return 1;
    }
    return 0;
}

/*
check if first input in the given line is a symbol decleration.
if its a symbol decleration, the function saves the symbol and advances the line pointer
to the end of the decleration.
return: NULL if no symbol decleration otherwise retrun the symbol.
*/
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
    /*add && != EOF becuse you might get a file that containes only one word*/
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

/*
This function checks if there is .data / .string directive in the curent line.
return: returns 0 if .data, returns 1 if .string.
*/
int checkIfDataDirective(char *line, int *lineIndex)
{
    int i = *lineIndex;
    int c, k = 0;
    char data[7];

    while (isspace(*(line + i)))
    {
        i++;
    }

    if (*(line + i) != '.')
    {

        return -1;
    }

    while ((c = *(line + i)) != ' ' && c != EOF && k < 7)
    {
        data[k] = c;
        i++;
        k++;
    }

    data[k] = '\0';

    if (strcmp(".data", data) == 0)
    {
        *lineIndex = i;
        return 0;
    }

    if (strcmp(".string", data) == 0)
    {
        *lineIndex = i;
        return 1;
    }

    if (strcmp(".extern", data) == 0)
    {
        *lineIndex = i;
        return 2;
    }

    if (strcmp(".entry", data) == 0)
    {
        *lineIndex = i;
        return 3;
    }

    return -1;
}

/*returns 0 if valid number else returns the char that encounterd*/
int getNumber(char *line, int *number, int *lineIndex)
{
    char numberString[75];
    int k = 0;
    int i = *lineIndex;
    int c, sign = 1;

    if (*(line + i) == '-')
    {
        sign = -1;
        i++;
    }
    else if (*(line + i) == '+')
    {
        i++;
    }

    while (isdigit(*(line + i)))
    {
        numberString[k] = *(line + i);
        i++;
        k++;
    }

    numberString[k] = '\0';
    c = *(line + i);

    if (c != ',' && c != ' ' && c != '\0')
    {
        return c;
    }
 
    *number = sign * atoi(numberString);
  
    *lineIndex = i;
   
    return 0;
}

int readAndSaveDataDirective_Data(char *line, int *lineIndex, int lineNumber)
{
    int getNumberStatus = 0;
    int number;
    /*check if there is at least on space betwen .data and a number*/
    if (*(line + *lineIndex) != ' ')
    {
        printf("line number %d Erorr: there must be at least one space between .data and the data itself", lineNumber);
        return 0;
    }

    /*skip all the white space between .data and the first argument*/
    while (isspace(*(line + *lineIndex)))
    {
        *lineIndex += 1;
    }

    do
    {
      
        getNumberStatus = getNumber(line, &number, lineIndex);
       
        if (getNumberStatus)
        {
            /*hnadle error*/
            printf("\nline number:%d Erorr: %c is not a valid number\n", lineNumber, getNumberStatus);

            return 0;
        }
        if (number > -2047 && number < 2047)
        {
            addData(number);
        }
        else
        {
            printf("\nline number %d Error: number %d is to big\n", lineNumber, number);
            return 0;
        }
   
    } while (checkIfSemicolon(line, lineIndex, lineNumber) != -1);

    return 1;
}

int readAndSaveString(char *line, int *lineIndex, int lineNmber)
{
    int i = *lineIndex;
    int c;

    if ((c = *(line + i)) != '"')
    {
        printf("line Number: %d Erorr: strign argument must start with \n", lineNmber);
        return 0;
    }

    i++;

    while ((c = *(line + i)) != '"')
    {
        if (c == '\0')
        {
            printf("line number: %d Erorr: string argument must end with: \n", lineNmber);
            return 0;
        }

        addData(c);
        i++;
    }

    addData(0);
    *lineIndex = ++i;
    return 1;
}

int readAndSaveStringDirective_data(char *line, int *lineIndex, int lineNumber)
{
    if (line[*lineIndex] != ' ')
    {
        printf("\nnumber line: %d Erorr: There must be at least one space between .string and the argument.\n", lineNumber);
        return 0;
    }

    while (isspace(*(line + *lineIndex)))
    {
        (*lineIndex)++;
    }

    if (readAndSaveString(line, lineIndex, lineNumber))
    {
        if (isNotSpace(line, lineIndex))
        {
            printf("number line: %d Error: only one argument allowed for .string", lineNumber);
            return 0;
        }
    }
    return 1;
}

char *getExternDirectiveSymbol(char *line, int *lineIndex)
{
    int i = *lineIndex;
    int c, k = 0;
    char *symbolArr = NULL;

    symbolArr = (char *)malloc(73);

    if (symbolArr == NULL)
    {
        printf("Error: error ocured while allocating memory");
        exit(0);
    }

    while (isspace(*(line + i)))
    {
        i++;
    }

    while ((c = *(line + i)) != ' ' && c != '\0')
    {
        symbolArr[k] = c;
        k++;
        i++;
    }

    *lineIndex = i;

    return symbolArr;
}

int readAndSaveExternalSymbol(char *line, int *lineIndex, int lineNumber)
{
    Symbol *externSymbol = NULL;
    char *externalSymbol = getExternDirectiveSymbol(line, lineIndex);

    if (isSymbolValid(externalSymbol, lineNumber) && !isSymbolDefined(externalSymbol, lineNumber) && !isRegisterName(externalSymbol, lineNumber))
    {
        externSymbol = createSymbol(externalSymbol, getDataCount(), "external", "\0");
        if (insertSymbol(externSymbol) == NULL)
        {
            if (!checkIfExternalAtribute(externSymbol))
            {
                printf("line number: %d Error: symbole arlready been defined it this file ", lineNumber);
                return 0;
            }
        }
        if (isNotSpace(line, lineIndex))
        {
            printf("line number: %d Error: .extern directive accept only one parameter\n.", lineNumber);
            return 0;
        }
    }
    return 1;
}

int saveInstructionLineSymbol(char *symbol, int lineNumber)
{
    Symbol *instSymbol = NULL;

    if (!isSymbolValid(symbol, lineNumber))
    {
        return 0;
    }

    instSymbol = createSymbol(symbol, getInstructionCount(), "code", "\0");
    insertSymbol(instSymbol);

    return 1;
}

char *getOperationName(char *line, int *lineIndex)
{
    int i = *lineIndex;
    int k = 0;
    int c;
    char *opName = (char *)malloc(80);

    while (isspace(*(line + i)))
    {
        i++;
    }

    while ((c = *(line + i)) != ' ' && c != '\0')
    {
        opName[k] = c;
        k++;
        i++;
    }

    opName[k] = '\0';
    *lineIndex = i;

    return opName;
}

Operands *readAndCodeOperands(char *operationName, char *line, int *lineIndex, int lineNumber)
{

    if (
        !strcmp(operationName, "mov") ||
        !strcmp(operationName, "cmp") ||
        !strcmp(operationName, "add") ||
        !strcmp(operationName, "sub") ||
        !strcmp(operationName, "lea"))
    {
        return handleTwoOperandsOperations(operationName, line, lineIndex, lineNumber);
    }
    else if (
        !strcmp(operationName, "clr") ||
        !strcmp(operationName, "not") ||
        !strcmp(operationName, "inc") ||
        !strcmp(operationName, "dec") ||
        !strcmp(operationName, "jmp") ||
        !strcmp(operationName, "bne") ||
        !strcmp(operationName, "jsr") ||
        !strcmp(operationName, "red") ||
        !strcmp(operationName, "prn"))
    {
        return handleOneOperandOperations(operationName, line, lineIndex, lineNumber);
    }
    else if (!strcmp(operationName, "rts") || !strcmp(operationName, "stop"))
    {
        return handleNoOperandsOperations(line, lineIndex, lineNumber);
    }

    return NULL;
}

Operands *handleTwoOperandsOperations(char *operationName, char *line, int *lineIndex, int lineNumber)
{
    Operands *operands = (Operands *)malloc(sizeof(Operands));
    int i = *lineIndex;

    if (operands == NULL)
    {
        printf("Error allocating memory");
        exit(0);
    }

    /* handle first operand*/
    if (readFirstOperand(operationName, operands, line, &i, lineNumber) == NULL)
    {
        free(operands);
        return NULL;
    }

    /*slip white space and check if there is semocolon between two arguments*/
    while (isspace(*(line + i)))
    {
        i++;
    }

    if (*(line + i) != ',')
    {
        printf("line number: %d Error: There must be a semicolon betwen two arguments", lineNumber);
        free(operands);
        return NULL;
    }

    i++;

    while (isspace(*(line + i)))
    {
        i++;
    }

    /*read second operand*/

    if (readSecondOperand(operationName, operands, line, &i, lineNumber) == NULL)
    {
        free(operands);
        return NULL;
    }

    if (isNotSpace(line, &i))
    {
        printf("line number: %d Error: line must be empty after arguments decleration\n", lineNumber);
        free(operands);
        return NULL;
    }

    operands->length = 2;
    *lineIndex = i;
    return operands;
}

Operands *handleOneOperandOperations(char *operationName, char *line, int *lineIndex, int lineNumber)
{
    Operands *operands = (Operands *)malloc(sizeof(Operands));
    if (operands == NULL)
    {
        printf("Error allocating memory");
        exit(0);
    }

    /* handle second operand*/
    if (readSecondOperand(operationName, operands, line, lineIndex, lineNumber) == NULL)
    {
        free(operands);
        return NULL;
    }

    if (isNotSpace(line, lineIndex))
    {
        printf("line number: %d Error: operation %s recives only one argument \n", lineNumber, operationName);
        free(operands);
        return NULL;
    }

    operands->length = 1;
    return operands;
}

Operands *handleNoOperandsOperations(char *line, int *lineIndex, int lineNumber)
{
    Operands *operands = (Operands *)malloc(sizeof(Operands));
    if (operands == NULL)
    {
        printf("Error allocating memory");
        exit(0);
    }
    if (isNotSpace(line, lineIndex))
    {
        printf("line number: %d Error: line must be empty after arguments decleration\n", lineNumber);
        free(operands);
        return NULL;
    }

    operands->length = 0;
    return operands;
}

Operands *readFirstOperand(char *operationName, Operands *operands, char *line, int *lineIndex, int lineNumber)
{
    char *opName;
    int addressingmode, number;

    opName = readOperand(line, lineIndex, lineNumber);
    if ((addressingmode = getOperandsAddressingMode(opName, lineNumber, &number)) >= 0)
    {
        operands->sourceOpAddresingMode = addressingmode;
    }
    else
    {
        return NULL;
    }
    if (isValidAddressingMode(operationName, 1, operands->sourceOpAddresingMode))
    {
        if (operands->sourceOpAddresingMode == 0)
        {
            operands->sourceOpBinaryCode = convertNumberToBinary(number);
        }
        if (operands->sourceOpAddresingMode == 1)
        {
            operands->sourceOpBinaryCode = NULL;
        }
        if (operands->sourceOpAddresingMode == 3)
        {
            operands->sourceOpBinaryCode = getRegisterAdress(opName);
        }
    }
    else
    {
        printf("line number: %d Error: %s is not a ligal operand for %s", lineNumber, opName, operationName);
        return NULL;
    }

    return operands;
}

Operands *readSecondOperand(char *operationName, Operands *operands, char *line, int *lineIndex, int lineNumber)
{
    char *opName;
    int number;
    opName = readOperand(line, lineIndex, lineNumber);

    operands->destenationOpAddressongMode = getOperandsAddressingMode(opName, lineNumber, &number);
    if (isValidAddressingMode(operationName, 2, operands->destenationOpAddressongMode))
    {
        if (operands->destenationOpAddressongMode == 0)
        {
            operands->destenationOpBinaryCode = convertNumberToBinary(number);
        }
        if (operands->destenationOpAddressongMode == 1)
        {
            operands->destenationOpBinaryCode = NULL;
        }
        if (operands->destenationOpAddressongMode == 2)
        {
            operands->destenationOpBinaryCode = NULL;
        }
        if (operands->destenationOpAddressongMode == 3)
        {
            operands->destenationOpBinaryCode = getRegisterAdress(opName);
        }
    }
    else
    {
        printf("line number: %d Error: %s is not a ligal operand for %s", lineNumber, opName, operationName);
        return NULL;
    }

    return operands;
}

char *createFirstWord(char *operationName, Operands *operands)
{
    int i = 0;
    char *opFunct = searchOpperation(operationName);
    char *word = (char *)malloc(12);

    if (word == NULL)
    {
        printf("\nError occured while allocating memory\n");
        exit(0);
    }

    for (; i < 8; i++)
    {
        word[i] = opFunct[i];
    }

    switch (operands->sourceOpAddresingMode)
    {
    case 0:
        word[8] = 0;
        word[9] = 0;
        break;

    case 1:
        word[8] = 0;
        word[9] = 1;
        break;

    case 2:
        word[8] = 1;
        word[9] = 0;
        break;

    case 3:
        word[8] = 1;
        word[9] = 1;
        break;

    default:
        break;
    }

    switch (operands->destenationOpAddressongMode)
    {
    case 0:
        word[10] = 0;
        word[11] = 0;
        break;

    case 1:
        word[10] = 0;
        word[11] = 1;
        break;

    case 2:
        word[10] = 1;
        word[11] = 0;
        break;

    case 3:
        word[10] = 1;
        word[11] = 1;
        break;

    default:
        break;
    }

    return word;
}

void saveFirstWord(char *word, Operands *operands)
{

    Instruction *firstWord = createInstruction(word, getInstructionCount(), operands->length, 'A');
    addInstructionToInstructionTable(firstWord);
}

void saveAdditionalWord(int addressingMode, char *binaryCode)
{
    switch (addressingMode)
    {
    case 0:
        if (binaryCode != NULL)
        {
            addInstructionToInstructionTable(createInstruction(binaryCode, getInstructionCount(), 1, 'A'));
        }
        break;

    case 1:
        incInstructionCount();
        break;

    case 2:
        incInstructionCount();
        break;

    case 3:
        if (binaryCode != NULL)
        {
            addInstructionToInstructionTable(createInstruction(binaryCode, getInstructionCount(), 1, 'A'));
        }
        break;

    default:
        break;
    }
}