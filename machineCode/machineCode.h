#define MEMORY_SIZE 3996


typedef struct DataNode
{
    struct DataNode *next;
    char *data;
    int memoryLocatin;
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
void incInstructionCount(void);
void printInstructionTable(void);
void changeMemoryLocation(int newMemoryLocation);
void printDataTable(void);
int getSecondRoundCounter(void);
Instruction *getInstruction(int position);
void increamentSecounRoundCounter(int inc);
/*char *getInstructionsBinaryCode(int memoryPos);*/
void saveInstructionAtSpecificPlace(char *instruction, int position, int memoryLocation, int length, char ARE);



