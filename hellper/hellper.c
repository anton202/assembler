#include <stdio.h>
#include <ctype.h>
#define LINE_LENGTH 80

/*
Reade line until new line char or EOF from file.
Max line length allowed is 80 char.
input: char array, file pointer, line number.
return: 1 if line length > 80, EOF if EOF, 0 if line successfully read
 */
int readLine(char *arr, FILE *fp, int lineNum)
{
    int c, lineLength = 1;
    while ((c = getc(fp)) != '\n' && c != EOF)
    {
        if (lineLength == LINE_LENGTH)
        {
            printf("Error: line %d is to long. max line length is 80 charecters\n", lineNum);
            *arr = '\0';
            while ((c = getc(fp)) != '\n' && c != EOF)
                ;

            return 1;
        }
        *arr++ = c;
        lineLength++;
    }
    if (c == EOF)
    {
        return EOF;
    }
    *arr = '\0';
    return 0;
}

int checkIfSemicolon(char *line, int *lineIndex, int lineNumber)
{
    int i = *lineIndex;

    while (isspace(*(line + i)))
    {
        i++;
    }

    if (*(line + i) == '\0')
    {
        return -1;
    }

    if (*(line + i) == ',')
    {

        i++;
        while (isspace(*(line + i)))
        {
            i++;
        }

        if (*(line + i) == '\0')
        {
            printf("\nline number: %d Error: data defenition line cannot end with: ',' ", lineNumber);
            return -1;
        }
        *lineIndex = i;
        return 1;
    }

    printf("\nline number: %d Error: numbers must be seperated by comma", lineNumber);
    return -1;
}
/*
This function checks if there are charecters in the given line that are not space chars.
return 1 if not space char was found. return 0 if only space chars found.
*/
int isNotSpace(char *line, int *lineIndex)
{
    int i = *lineIndex;
    while (isspace(*(line + i)))
    {
        i++;
    }

    if (*(line + i) == '\0')
    {
        *lineIndex = i;
        return 0;
    }

    *lineIndex = i;
    return 1;
}

int checkForNotAlphaNumericChars(char *symbol)
{
    int i;

    for (i = 0; *(symbol + i) != '\0'; i++)
    {
        if (!isalnum(*(symbol + i)))
        {
            return 0;
        }
    }
    return 1;
}