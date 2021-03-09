#include<stdio.h>
#include<stdlib.h>
#include "machineCode.h"
#include "../utility/utility.h"

int DC = 0;
Data *head = NULL;

Data *addData(int number)
{
    Data *node = head;
    Data *dataNode = createDataNode(number);

    /*
        if((DC + getCodeCounter()) > 4095)
        {
            printf("Error: not enough memory space");
            exit(0);
        }
    */

    if(head == NULL)
    {
        head = dataNode;
        DC++;
        return head;
    }

    while (node->next != NULL)
    {
        node = node->next;
    }

    node->next = dataNode;
    DC++;
    return node->next;
    
}

Data *createDataNode(int number)
{
    char **pNumber = convertNumberToBinary(number);
    Data *dataNode = (Data *)malloc(sizeof(Data));

    dataNode->next = NULL;
    dataNode->data = *pNumber;

    return dataNode;
}