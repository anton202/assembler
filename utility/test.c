#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utility.h"

char *converBinaryToHex(char *binaryNumber);

int main(void)
{
     char binary[12] = {0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
     char *hexNUm = converBinaryToHex(binary);
     printf("\nhex number: %s\n",hexNUm);
   
    
     
     return 1;
}

char *converBinaryToHex(char *binaryNumber)
{
     int counter = 0;
     int i, sum = 0;
     int hexPos = 2;
     char *hexNum = (char *)malloc(4);

     if (hexNum == NULL)
     {
          printf("\nError ocured while allocation memory for output file\n");
          exit(0);
     }

     for (i = 11; i >= 0; i--)
     {
          if (counter < 3)
          {
               sum += (binaryNumber[i]) * pow(2, counter);
               counter++;
          }
          else
          {
               sum += (binaryNumber[i]) * pow(2, (counter));
               switch (sum)
               {
               case 10:
                    hexNum[hexPos] = 'A';
                    break;

               case 11:
                    hexNum[hexPos] = 'B';
                    break;

               case 12:
                    hexNum[hexPos] = 'C';
                    break;

               case 13:
                    hexNum[hexPos] = 'D';
                    break;

               case 14:
                    hexNum[hexPos] = 'E';
                    break;

               case 15:
                    hexNum[hexPos] = 'F';
                    break;

               default:
                    hexNum[hexPos] = 48 + sum;
                    break;
               }

               hexPos--;
               sum = 0;
               counter = 0;
          }
     }
     hexNum[3] = '\0';
     return hexNum;
}