#include <stdio.h>
#include <ctype.h>
#include "firstRun.h"
#include "../hellper/hellper.h"
#include "../utility/utility.h"
#include "../machineCode/machineCode.h"

int main(int argc, char *argv[])
{
    char line[80];
    FILE *fp;
    int lineReadStatus;
    char *symbol;
    int lineIndex = 0;
    int isDataDirective;

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

    if (lineReadStatus != 1)
    {

        symbol = isSymbol(line, &lineIndex);
        if (symbol != NULL)
        {
            printf("the symbol is: %s \n", symbol);
            isSymbolValid(symbol, 1);
        }
        printf("\nline index: %d\n", lineIndex);

        isDataDirective = checkIfDataDirective(line, &lineIndex);
        if (!isDataDirective)
        {
            readAndSaveDataDirective_Data(line, &lineIndex);
        }
        else if (isDataDirective == 1)
        {
           printf("\n%d\n",'\0');
            if (line[lineIndex] != ' ')
            {
                printf("\nnumber line: %d Erorr: There must be at least one space between .string and the argument.\n", 1);
                return 0;
            }

            while (isspace(*(line + lineIndex)))
            {
                lineIndex++;
            }

            readAndSaveString(line, &lineIndex, 1);
        }
    }

    return 1;
}