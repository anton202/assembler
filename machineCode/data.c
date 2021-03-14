#include<stdio.h>
#include<stdlib.h>
#include "machineCode.h"
#include "../utility/utility.h"

static int DC = 0;
static Data *head = NULL;

static Data *createDataNode(int number)
{
    char *pNumber = convertNumberToBinary(number);
    Data *dataNode = (Data *)malloc(sizeof(Data));

    dataNode->next = NULL;
    dataNode->data = pNumber;

    return dataNode;
}

Data *addData(int number)
{
    Data *node = head;
    Data *dataNode = createDataNode(number);

    
        if((DC + getInstructionCount()) < MEMORY_SIZE)
        {
            printf("Error: not enough memory space");
            exit(0);
        }
    

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

int getDataCount(void)
{
    return DC;
}