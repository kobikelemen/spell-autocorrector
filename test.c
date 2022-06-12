#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
    FILE *file = fopen("text_to_check.txt", "r+");
    fseek(file, 3, SEEK_SET);
    char * s =  "yo mama";
    fwrite(s, strlen(s), 1, file);
    fclose(file);
}