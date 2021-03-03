#include <stdio.h>
#include "./utility/utility.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("\nError: Please enter file name\n");
        return 0;
    }

    if(checkFiles(argc,argv) == -1)
    {
        return 0;
    }
    

    return 1;
}

/*
printf("\nNumber of arguments passed: %d\n",argc);
for(i = 1; i < argc; i++){
        printf("\n%s\n",argv[i]);

}
*/