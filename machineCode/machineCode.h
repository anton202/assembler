typedef struct DataNode
{
    struct DataNode *next;
    char *data;
    
}Data;


Data *addData(int number);