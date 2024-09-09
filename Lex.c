#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "list.h"

int main(int argc, char *argv[]) {
    FILE *input = NULL;
    FILE *output = NULL;
    if(argc!= 2){
        fprintf(stderr, "Usage: Lex <input file> <output file>");
        return 1;
    }
    input = fopen(argv[0], "r");
    if(input == NULL){
        fprintf(stderr, "Lex: error reading input file %s", argv[0]);
        return 1;
    }
    output = fopen(argv[1], "w");
    if(output == NULL){
        fprintf(stderr, "Lex: error reading output file %s", argv[1]);
        return 1;
    }
    int lines = 0;
    while((current= fgetc(input)) != EOF){
        if(current = '\n'){
            lines++;
        }
    }
    char **array = calloc(lines, sizeof(char*));
    for(int i = 0; i < lines; i++){
        array[i]= calloc(256, sizeof(char)); //figure out how long
         
    }




}
    
