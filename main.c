

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ALPHA 27
#define DICT_SIZE 10
#define MAX_WORD 256



typedef struct bucket
{
    char* word;
    struct bucket *next;
} bucket;


bucket * hash_table[DICT_SIZE];
const unsigned MAX_TEXT = 1000;
char *text[MAX_TEXT];




int hash(char s[]) { 
    int size = strlen(s);
    int num = pow(ALPHA, size);
    for (int i=0; i < size-1; i++) {
        num += pow(ALPHA, size-i-1) * (s[i]-96);
    }
    return num % DICT_SIZE;
}


void print_bucket(bucket* b)
{
    if (b == NULL) {
        return;
    }
    printf("\t%s", b->word);
    print_bucket(b->next);
}


void print_array()
{
    int len = DICT_SIZE;
    for (int i=0; i < len; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i", i);
            print_bucket(hash_table[i]);
        }
    }
    printf("\n\n");
}


void create_dict()
{
    char *filename = "words.txt";
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
    }
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, fp)){
        int h = hash(buffer);
        bucket *b = malloc(sizeof(struct bucket));
        b->word = malloc(strlen(buffer));
        strcpy(b->word, buffer);
        if (hash_table[h] == NULL) {
            
            b->next = NULL;
            hash_table[h] = b;
        } else {
            b->next = hash_table[h];
            hash_table[h] = b;
        }
    }
    print_array();
    fclose(fp);
}


void get_text()
{
    char* filename = "text_to_check.txt";
    FILE* fp = fopen(filename, "r");

    const unsigned MAX_LINE = 256;
    char line[MAX_LINE];
    int i=0;
    char *cp;
    char *bp;

    while (fgets(line, MAX_LINE, fp) != NULL) {
        bp = line;
        while (1) {
            cp = strtok(bp, " ");
            bp = NULL;
            if (cp == NULL) {
                break;
            }
            text[i++] = cp;
        }
    }
}




int main() 
{

    for (int i=0; i < DICT_SIZE; i++) {
        hash_table[i] = NULL;
    }

    get_text();
    create_dict();
    print_array();
    // for (int i=0; i < DICT_SIZE; i++) {
    //     free(*hash_table[i]);
    // }
    // printf("\n\n\n");
    // free(hash_table);

    // need to free
    return 0;
    




}