
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DICT_SIZE 10000
#define MAX_WORD 20
int ALPHA = 27;
int num_errors = 0;




typedef struct bucket
{
    char* word;
    struct bucket *next;
} bucket;


int hash(char s[]);


typedef struct string_list
{
    char * str;
    struct string_list * next;
} string_list;


void print_string_list(string_list *sl)
{
    printf("%s  ", sl->str);
    if (sl->next == NULL) {
        printf("\n\n");
        return;
    }
    print_string_list(sl->next);
}


void append_string_list(string_list **l, char * s)
{   
    string_list * end = malloc(sizeof(string_list));
    end->str = s;
    end->next = *l;
    *l = end;
}


int check_in_string_list(string_list * sl, char * s)
{
    if (sl->str == NULL) {
        return 0;
    }
    if (strcmp(sl->str, s) == 0) {
        return 1;
    }
    if (sl->next == NULL) {
        return 0;
    }
    check_in_string_list(sl->next, s);
    return 0;
}





int is_word_in(bucket* b, char* w)
{
    
    if (b == NULL) {
        return 0;
    } 
    
    if (strcmp(b->word,w) == 0) {
        return 1;
    }
    return is_word_in(b->next, w);
}



struct list
{
    int v;
    struct list *next;
};


void print_list(int *list, int size)
{
    printf("\n\n Text indexes: \n");
    for (int i=0; i < size; i++) {
        if (list[i] == -1) {
            return;
        }
        printf("%i, ", list[i]);
    }
    printf("\n\n");
}



bucket * hash_table[DICT_SIZE];
const unsigned MAX_TEXT = 50;
char *text[MAX_TEXT];


void print_text(){
    printf("\n\nThe text:\n");
    for (int i=0; i < MAX_TEXT; i++){
        printf("%s\n", text[i]);
    }
}




string_list * edit_dist1(char * str)
{
    string_list * strings = malloc(sizeof(string_list));
    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
    int MAX_WOOOORD = 20;


    // remove character check - 
    int str_len = strlen(str);
    int h = 0;
    char checker[MAX_WORD];
    for (int i=0; i < str_len; i++) {

        strcpy(checker, str);
        // remove character

        memmove(&checker[i], &checker[i+1], strlen(checker) - i);
        h = hash(checker);
        if (is_word_in(hash_table[h], checker)) {
            if ((check_in_string_list(strings, checker) == 0)){ // in future speed up by not checking if str is already in string list, 
                //                                              instead use hueristic since know that fails when extra letter is same as one before in the str

                printf("hash: %i   ", h);
                char * correct_word;
                strcpy(correct_word, checker);
                append_string_list(&strings, correct_word);
            }
        }
        

        // insert character
       for (int alph=0; alph < 26; alph++)
       {
            char checker[str_len+1];
            strncpy(checker, str, i);
            char a[1];
            a[0] = alphabet[alph];
            strcpy(checker+i, a);
            strcpy(checker+i+1, str+i);
            h = hash(checker);
            // printf("final checking: %s\n", checker);
            if (is_word_in(hash_table[h], checker)) {
                if ((check_in_string_list(strings, checker) == 0)){
                    printf("\n\nhash: %i \n", h);
                    printf("successful checker: %s\n", checker);
                    char * correct_word = malloc(sizeof(checker));
                    strcpy(correct_word, checker);

                    printf("correct word: %s\n", correct_word);
                    append_string_list(&strings, correct_word);
                    printf("current string list: \n");
                    print_string_list(strings);
                }
            }
        }

    }
    // printf("\nstrings: \n");
    // print_string_list(strings);

    return strings;
}





int hash(char s[]) { 

    int length = strnlen(s, MAX_WORD);
    int hash_value = 0;
    for (int i=0; i < length; i++) {
        hash_value += s[i];
        hash_value = (hash_value * s[i]);// % DICT_SIZE;
    }
    
    hash_value = abs(hash_value) % DICT_SIZE;
    
    return hash_value;
}




void print_bucket(bucket* b)
{
    if (b == NULL) {
        return;
    }
    printf("\t%s", b->word);
    print_bucket(b->next);
}





void print_dict()
{
    int len = DICT_SIZE;
    for (int i=0; i < len; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i", i);
            print_bucket(hash_table[i]);
            printf("\n");
        }
    }
    printf("\n\n");
}



void print_array(char *a[MAX_TEXT])
{
    printf("\n\n\nThe text: \n\n");
    for (int i=0; i < MAX_TEXT; i++) {
        printf("%s ", a[i]);
    }
    printf("\n\n\n");
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
        buffer[strcspn(buffer, "\n")] = 0;
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
    print_dict();
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
            text[i] = malloc(MAX_WORD);
            strcpy(text[i], cp);
            i++;
        }
    }

}






int* spell_errors()
{
    /*
    Returns indexes of text which contain spelling errors
    */

    int t = 0;
    int e = 0;
    int h = 0;
    char* word = text[t];
    int *err_indx = (int *)malloc(sizeof(int) * MAX_TEXT);
    int hashes[MAX_TEXT]; // gives errors hash (so dictionary position)

    while (word != NULL) {
        
        h = hash(word);        
        if (!is_word_in(hash_table[h], word)) {
            printf("\n\nspelling error: %s\n" ,word);
            printf("corresponding hash value: %i\n", h);
            err_indx[e] = t; // gives position in text
            num_errors++;
            e++;
        }
        t++;
        word = text[t];
    }
    err_indx[e] = -1;
    return err_indx;
}



void correct_text(int error_indexes[])
{
    
    for (int i=0; i < num_errors; i++) {
        string_list *ed1;
        ed1 = edit_dist1(text[error_indexes[i]]);
        strcpy(text[error_indexes[i]], ed1->str); // just take first string w/ edit dist. 1

    }
    printf("\n\nThe edited text:");
    print_text();
    FILE *file = fopen("text_to_check.txt", "w");
    int i = 0;
    while (text[i] != NULL){
        fprintf(file, "%s ",text[i]);
        i++;
    }
    fclose(file);
}




int main() 
{

    for (int i=0; i < DICT_SIZE; i++) {
        hash_table[i] = NULL;
    }

    get_text();
    print_array(text);
    create_dict();
    print_dict();
    int *error_indexes = spell_errors();
    print_list(error_indexes, MAX_TEXT);
    correct_text(error_indexes);

    return 0;    

}
