#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../tables/tables.h"
#include "../tables/symbolTable/symbolTable.h"
#include "../hellper/hellper.h"
#include "../machineCode/machineCode.h"
#include "../utility/utility.h"

#define MAX_NUMBER 2047
#define MIN_NUMBER -2047
#define NUMBER_LENGTH 4
#define MAX_SYMBOL_LENGTH 31
#define MAX_STRING_LENGTH 70

typedef struct OperandsData
{
    char sourceOpAddresingMode;
    char destenationOpAddressongMode;
    char length;
    char *sourceOpBinaryCode;
    char *destenationOpBinaryCode;
} Operands;

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

int isSymbolValid(char *symbol, int lineNumber)
{
    if (strlen(symbol) > MAX_SYMBOL_LENGTH)
    {
        printf("\n line number: %d :Error: symbol name must be less than 31 characters.", lineNumber);
        free(symbol);
        return 0;
    }
    if (!isalpha(*symbol))
    {
        printf("\nline number: %d Error: symbol name must start with an alphabetic letter.", lineNumber);
        free(symbol);
        return 0;
    }
    if (!strcmp(symbol, "data") || !strcmp(symbol, "string") || !strcmp(symbol, "entry") || !strcmp(symbol, "extern"))
    {
        printf("line number: %d Error: %s is a saved word in assembly", lineNumber, symbol);
        free(symbol);
        return 0;
    }
    if (isdigit(*symbol))
    {
        printf("\nline number: %d Error: symbol name can`t begin with a digit.", lineNumber);
        free(symbol);
        return 0;
    }

    if (!checkForNotAlphaNumericChars(symbol))
    {
        printf("line number: %d Error: symbol name must only contain aqalphabet or number charecters\n", lineNumber);
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
        free(symbol);
        return 0;
    }
    return 1;
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

    if (c != ',' && c != ' ')
    {
        return c;
    }

    *number = sign * atoi(numberString);
    *lineIndex = i;
    return -1;
}

int readAndSaveDataDirective_Data(char *line, int *lineIndex)
{
    int getNumberStatus = 0;
    int number;
    /*check if there is at least on space betwen .data and a number*/
    if (*(line + *lineIndex) != ' ')
    {
        printf("line number %d Erorr: there must be at least one space between .data and the data itself", 1);
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
        if (getNumberStatus > -1)
        {
            /*hnadle error*/
            printf("\nline number:%d Erorr: %c is not a valid number\n", 1, getNumberStatus);
            return 0;
        }
        if (number > -2047 && number < 2047)
        {
            addData(number);
            printf("\nnumber read: %d", number);
        }
        else
        {
            printf("\nnumber line %d Error: number %d is to big\n", 1, number);
            return 0;
        }

    } while (checkIfSemicolon(line, lineIndex, 1) != -1);

    return 1;
}

int readAndSaveString(char *line, int *lineIndex, int *lineNmber)
{
    int i = *lineIndex;
    Data *test;
    int c, k;

    if ((c = *(line + i)) != '"')
    {
        printf("line Number: %d Erorr: strign argument must start with \" ", *lineNmber);
        return 0;
    }

    i++;

    while ((c = *(line + i)) != '"')
    {
        if (c == '\0')
        {
            printf("line number: %d Erorr: string argument must end with: \" ", *lineNmber);
            return 0;
        }

        test = addData(c);
        /*T E S T  - DELETE THIS*/

        for (k = 0; k < 12; k++)
        {
            printf(" %d ", *(test->data + k));
        }
        putchar('\n');

        /*UNTIL HERE*/
        i++;
    }

    addData(0);
    *lineIndex = ++i;
    return 1;
}

int readAndSaveStringDirective_data(char *line, int *lineIndex, int *lineNumber)
{
    if (line[*lineIndex] != ' ')
    {
        printf("\nnumber line: %d Erorr: There must be at least one space between .string and the argument.\n", 1);
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
            printf("number line: %d Error: only one argument allowed for .string", *lineNumber);
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

    if (isSymbolValid(externalSymbol, lineNumber))
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
        printHead();
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
    Operands *operands = (Operands *)malloc(sizeof(Operands));
    char *opName;
    char opAddressingMode;
    int i = *lineIndex;
    if (
        !strcmp(operationName, "mov") ||
        !strcmp(operationName, "cmp") ||
        !strcmp(operationName, "add") ||
        !strcmp(operationName, "sub") ||
        !strcmp(operationName, "lea"))
    {
        /*handle firts operand*/
        opName = readOperand(line, lineIndex, lineNumber);
        operands->sourceOpAddresingMode = getOperandsAddressingMode(opName);
        if (isSourceOpAddressingModeValid(operands->sourceOpAddresingMode))
        {
            if (operands->sourceOpAddresingMode == 0)
            {
                operands->sourceOpBinaryCode = convertNumberArgToBinary(opName);
            }
            if (operands->sourceOpAddresingMode == 1)
            {
                operands->sourceOpBinaryCode = NULL;
            }
            if (operands->sourceOpAddresingMode == 3)
            {
                operands->sourceOpBinaryCode = registerCode(opName);
            }
        }else{
            printf("line number: %d Error: %s is not ligal operand for %s",lineNumber,opName,operationName);
            return NULL;
        }
        /* handle second operand*/

        /*slip white space and check if there is semocolon between two arguments*/
        while (isspace(*(line + *lineIndex)))
        {
            *lineIndex++;
        }
        if(*(line + *lineIndex) != ',')
        {
            printf("line number: %d Error: There must be a semicolon betwen two arguments",lineNumber);
            return NULL;
        }
         while (isspace(*(line + *lineIndex)))
        {
            *lineIndex++;
        }

    opName = readOperand(line, lineIndex, lineNumber);        
    operands->destenationOpAddressongMode = getOperandsAddressingMode(opName);
    if (isDestenationOpAddressingModeValid(operands->destenationOpAddressongMode))
    {
        if (operands->destenationOpAddressongMode == 0)
            {
                operands->destenationOpBinaryCode = convertNumberArgToBinary(opName);
            }
            if (operands->destenationOpAddressongMode == 1)
            {
                operands->destenationOpBinaryCode = NULL;
            }
            if (operands->destenationOpAddressongMode == 3)
            {
                operands->destenationOpBinaryCode = registerCode(opName);
            }
    }else{
            printf("line number: %d Error: %s is not ligal operand for %s",lineNumber,opName,operationName);
            return NULL;
        }

        if(isNotSpace(line, lineIndex))
        {
            printf("line number: %d Error: line must be empty after arguments decleration\n",lineNumber);
            return NULL;
        }

        operands->length = 2;
        return operands;
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
    }
    else if (!strcmp(operationName, "rts") || !strcmp(operationName, "stop"))
    {
    }

    return NULL;
}