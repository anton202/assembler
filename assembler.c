#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "./firstRun/firstRun.h"
#include "./hellper/hellper.h"
#include "./utility/utility.h"
#include "./tables/tables.h"
#include "./machineCode/machineCode.h"
#include "./tables/symbolTable/symbolTable.h"

int main(int argc, char *argv[])
{
    char line[80];
    FILE *fp;
    int lineNumber = 1;
    int error = 0;
    int i = 1;
    int ICF;

    if (argc == 1)
    {
        printf("\nError: Please enter file name\n");
        return 0;
    }

    if (checkFiles(argc, argv) == -1)
    {
        return 0;
    }

    for (; i < argc; i++)
    {
        fp = fopen(addExtentitonToFileName(argv[i], ".as"), "r");

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

        if(error)
        {
            return 0;
        }
        /*
        create output files
        */

        createObjectFile(argv[i]);
        createExtFile(argv[i]);
        createEntFile(argv[i]);

        resetDataTable();
        resetInstructionTabale();
        resetSymbolTable();
        resetExternalSymbolTable();
        lineNumber = 1;
        error = 0;
        ICF = 0;
    }

    return 1;
}

