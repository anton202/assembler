#include <string.h>

#define REGISTER_TABLE_SIZE 8
typedef struct RegisterData
{
    char *name;
    char adress[12];
} Register;

Register registersTable[REGISTER_TABLE_SIZE] = {
    {"r0", {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    {"r1", {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}},
    {"r2", {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}},
    {"r3", {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}},
    {"r4", {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}},
    {"r5", {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}},
    {"r6", {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}},
    {"r7", {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}}};


/*returns 1 if register name exist in table. else returns 0*/
int searchRegisterName(char *rName)
{
    int i = 0;
    for (; i < REGISTER_TABLE_SIZE; i++)
    {
        if (strcmp(registersTable[i].name, rName) == 0)
        {
            return 1;
        }
    }
    return 0;
}

char *getRegisterAdress(char *rName)
{
    int i = 0;
    for (; i < REGISTER_TABLE_SIZE; i++)
    {
        if (strcmp(registersTable[i].name, rName) == 0)
        {
            return registersTable[i].adress ;
        }
    }
    return 0;
}