#include <stdio.h>
#include "hellper.h"

int main(int argc, char *argv[]){
    char line[81];
    FILE *fp;
    int lineNum = 1;
    int status;

    fp = fopen(argv[1],"r");
    
    if(fp != NULL)
    {
        while ((status=readLine(line, fp,lineNum)) != EOF )
        {
           printf("%s\n",line);
           lineNum++;
        }
        
   
    }

    return 1;

}