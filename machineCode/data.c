#include<stdio.h>
#include "machineCode.h"

int DC = 0;
Data *head = NULL;

Data *addData(Data *data)
{
    Data *node = head;

    /*
        if((DC + getCodeCounter()) > 4095)
        {
            printf("Error: not enough memory space");
            exit(0);
        }
    */

    if(head == NULL)
    {
        head = data;
        DC++;
        return data;
    }

    while (node->next != NULL)
    {
        node = node->next;
    }

    node->next = data;
    DC++;
    return node->next;
    
}

