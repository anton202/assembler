char *isSymbol(char *line, int *lineIndex);
int isSymbolValid(char *symbol, int lineNumber);
int checkIfDataDirective(char *line, int *lineIndex);
int checkDataFormat(char *line, int *lineIndex, int *saveNumber, int lineNumber);

