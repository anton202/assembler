typedef struct SymbolNode{
	struct SymbolNode *next;
	char *symbol;
	int value;
	char *attributes[2];
}Symbol;


Symbol *insertSymbol(Symbol *entry);
Symbol *searchSymbol(char *symbolName );
Symbol *createSymbol(char *symName, int value, char *atr1, char *atr2);
int checkIfExternalAtribute(Symbol *externSymbol);
void printHead();
