#include <stdio.h>
#include "./machineCode.h"

int main(void)
{
    int i;
    Data *saved = addData(234);
    addData(44);
    addData(33);
    addData(3);
    addData(1);
    addData(6);
    addData(1000);
    addData(0);
    addData(14);
    addData(27);
    addData(777);
    addData(987);
    addData(8);

    while (saved != NULL)
    {
        printf("The data that was saved: ");

        for (i = 0; i < 12; i++)
        {
            printf("%d ", *(saved->data + i));
        }
        putchar('\n');
        saved = saved->next;
    }

    return 1;
}