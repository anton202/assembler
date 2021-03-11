char *isSymbol(char *line, int *lineIndex);
int isSymbolValid(char *symbol, int lineNumber);
int checkIfDataDirective(char *line, int *lineIndex);
int getNumber(char *line,int *number, int *lineIndex);
int readAndSaveDataDirective_Data(char *line, int *lineIndex);
int readAndSaveString(char *line, int *lineIndex, int lineNmber);


