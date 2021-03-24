#define MAX_SYMBOL_LENGTH 31

int checkFiles(int length, char **fileName);
char *addExtentitonToFileName(char *fileName);
char *convertNumberToBinary(int number);
char *readOperand(char *line, int *lineIndex, int lineNumber);
int isImmedtiateOperand(char *operand, int lineNumber, int *number);
int getOperandsAddressingMode(char *operand, int lineNumber, int *number);
int isSymbolValid(char *symbol, int lineNumber);
int isSymbolDefined(char *symbol,int lineNumber);
int isRegisterName(char *symbol, int lineNumber);
int isRelativeOPerand(char *opernad,int lineNuber);
char *convertNumberOpToBinary(char *operand, int lineNumber);

