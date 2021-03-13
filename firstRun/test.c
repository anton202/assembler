#include <stdio.h>
#include <ctype.h>
#include "firstRun.h"
#include "../hellper/hellper.h"
#include "../utility/utility.h"
#include "../machineCode/machineCode.h"
#include "../tables/symbolTable/symbolTable.h"

int main(int argc, char *argv[])
{
    char line[80];
    FILE *fp;
    int lineReadStatus;
    char *symbol;
    int lineIndex = 0;
    int isDataDirective, lineNumber = 1;
    char *externalSymbol;
    Symbol *externSymbol;

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

            readAndSaveStringDirective_data(line, &lineIndex, &lineNumber);
        }
        else if (isDataDirective == 2)
        {
           
            externalSymbol = getExternDirectiveSymbol(line, &lineIndex);
            if (isSymbolValid(externalSymbol, lineNumber))
            {
               externSymbol = createSymbol(externalSymbol,0,"external","\0");
               if(insertSymbol(externSymbol) == NULL)
               {
                   if(!checkIfExternalAtribute(externSymbol))
                   {
                       printf("line number: %d Error: symbole arlready been defined it this file ",lineNumber);
                       return 0;
                   }
               }
               /*check if there are aditional chares on the line after extern symbol*/
              printHead();
            }
        }
    }

    return 1;
}