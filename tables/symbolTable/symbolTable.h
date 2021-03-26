typedef struct SymbolNode
{
	struct SymbolNode *next;
	char *symbol;
	int value;
	char *attributes[2];
} Symbol;

typedef struct ExternalSymbol
{
	char *name;
	int value;
	struct ExternalSymbol *next;
} ExternSymbol;

Symbol *insertSymbol(Symbol *entry);
Symbol *searchSymbol(char *symbolName);
Symbol *createSymbol(char *symName, int value, char *atr1, char *atr2);
int checkIfExternalAtribute(Symbol *externSymbol);
ExternSymbol *insertExternalSymbol(ExternSymbol *entry);
ExternSymbol *createExternalSymbol(char *symName, int value);
void printHead();
void printSymbolTable(void);
void changeSymbolMemoryLocation(int newMemoryLocation);