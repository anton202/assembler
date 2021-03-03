#include <string.h>

char *registersNames[] = {
    "r1", "r2", "r3", "r4", "r5", "r6", "r7", "-1"};

/*returns 1 if register name exist in table. else returns 0*/
int searchRegisterName(char *rName)
{
    int i = 0;
    while (strcmp(registersNames[i], "-1") != 0)
    {
        if (strcmp(registersNames[i], rName) == 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}