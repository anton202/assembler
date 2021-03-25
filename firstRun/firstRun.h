typedef struct OperandsData
{
    char sourceOpAddresingMode;
    char destenationOpAddressongMode;
    char length;
    char *sourceOpBinaryCode;
    char *destenationOpBinaryCode;
} Operands;

int commentLine(char *line);
int emptyLine(char *line, int *lineIndex);
char *isSymbol(char *line, int *lineIndex);
int isSymbolValid(char *symbol, int lineNumber);
int checkIfDataDirective(char *line, int *lineIndex);
int getNumber(char *line,int *number, int *lineIndex);
int readAndSaveDataDirective_Data(char *line, int *lineIndex, int lineNumber);
int readAndSaveString(char *line, int *lineIndex, int lineNmber);
int readAndSaveStringDirective_data(char *line, int *lineIndex, int lineNumber);
char *getExternOrEntryDirectiveSymbol(char *line, int *lineIndex);
int readAndSaveExternalSymbol(char *line, int *lineIndex, int lineNumber);
int saveInstructionLineSymbol(char *symbol, int lineNumber);
char *getOperationName(char *line, int *lineIndex);
Operands *readAndCodeOperands(char *operationName, char *line, int *lineIndex, int lineNumber);
Operands *handleTwoOperandsOperations(char *operationName, char *line, int *lineIndex, int lineNumber);
Operands *handleOneOperandOperations(char *operationName, char *line, int *lineIndex, int lineNumber);
Operands *handleNoOperandsOperations(char *line, int *lineIndex, int lineNumber);
Operands *readFirstOperand(char *operationName, Operands *operands, char *line, int *lineIndex, int lineNumber);
Operands *readSecondOperand(char *operationName, Operands *operands, char *line, int *lineIndex, int lineNumber);
char *createFirstWord(char *operationName, Operands *operands);
void saveFirstWord(char *word, Operands *operands);
void saveAdditionalWord(int addressingMode, char *binaryCode);
int readAndSaveEntryDirectiveSymbol(char *line, int *lineIndex, int linenNumber);





