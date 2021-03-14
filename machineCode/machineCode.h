#define MEMORY_SIZE 3996


typedef struct DataNode
{
    struct DataNode *next;
    char *data;
    
}Data;


typedef struct InstructionData
{
    char *instruction;
    int memoryLocation;
    int instructionLength;
    char ARE;

}Instruction;



Data *addData(int number);
int getDataCount(void);
Instruction *createInstruction(char *instruction,int memoryLocation, int length, char ARE);
int getInstructionCount(void);
int addInstructionToInstructionTable(Instruction *inst);


