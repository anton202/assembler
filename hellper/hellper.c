#include <stdio.h>
#define LINE_LENGTH 80

/*
Reade line until new line char or EOF from file.
Max line length allowed is 80 char.
input: char array, file pointer, line number.
return: 1 if line length > 80, EOF if EOF, 0 if line successfully read
 */
int readLine(char *arr, FILE *fp,int lineNum)
{
    int c, lineLength = 1;
    while ((c = getc(fp)) != '\n' && c != EOF)
    {
        if (lineLength == LINE_LENGTH)
        {
            printf("Error: line %d is to long. max line length is 80 charecters\n", lineNum);
            *arr = '\0';
            while ((c = getc(fp)) != '\n' && c != EOF);
            
            return 1;
        }
        *arr++ = c;
        lineLength++;
    }
     if(c == EOF)
        {
            return EOF;
        }
        *arr = '\0';
    return 0;
}