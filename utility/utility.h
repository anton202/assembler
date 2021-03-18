int checkFiles(int length, char **fileName);
char *addExtentitonToFileName(char *fileName);
char *convertNumberToBinary(int number);
char *readOperand(char *line, int *lineIndex, int lineNumber);
int isImmedtiateOperand(char *operand, int lineNumber);
int getOperandsAddressingMode(char *operand, int lineNumber);
