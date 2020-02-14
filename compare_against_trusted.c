//Some additional debugging needed
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX_STR_LEN 1024
#define too_close 4

int type; // 1 is domain 2 is url
char file_content[MAX_STR_LEN];

bool in_text(char letter, char text[MAX_STR_LEN]){
//check if in text
    for (int i = 0; text[i] != '\0'; i++ ){
        if (letter == text[i]){
            return true;
        }
    }return false;
}

int check_type_input(char text[MAX_STR_LEN]){
    int type;
    if (in_text('@', text) && in_text('.', text)){
        type = 1; //domain
    }else{
        type = 2; //url
    }

}

int minimum(int a, int b, int c){
    if (a < b && a < c){
        return a;
    }else if (b < a && b < c){
        return b;
    }
    return c;
}

int compare(char whitelist[MAX_STR_LEN], int len1 ,char found[MAX_STR_LEN], int len2){
    //compute Levenshtein Distance between strings, degree of similarity between them, indicative of potential spoof
    //computes total number of deletions, insertions, and/or substitutions required to change s1 to s2 (and vice versa)
    char s1[MAX_STR_LEN];
    strcpy(s1, whitelist);
    char s2[MAX_STR_LEN];
    strcpy(s2, found);
    int counter;
    //base case of len1 or len2 being 0. If len1 is 0, then it would take len2 deletions to transform it to s1
    if (len1 == 0){
        return len2;
    }else if (len2 == 0){
        return len1;
    }

    if(s1[len1 - 1] == s2[len2 -1]){
        counter = 0;
    }else{
        counter = 1;
    }

    return minimum(compare(s1, len1 -1, s2, len2)+1,
                   compare(s1, len1, s2, len2-1) + 1, //using a recursive definition allows us to be thorough while being concise
                   compare(s1, len1-1, s2, len2 -1) + counter);
}

bool return_bool(char input[MAX_STR_LEN], FILE *file){
    char myArray[MAX_STR_LEN];
    char buffer[MAX_STR_LEN];
    int lines = 0;

    while (lines < 500){//fgets(buffer, 500, file) != NULL){
        strcpy(&myArray[lines], buffer);
        if (compare(&myArray[lines], strlen(&myArray[lines]), input, strlen(input))<= too_close){
            return true;
            break;
        }lines++;
    } return false;
}

int main(){
    FILE *whitelisted_domains = fopen("C:\\Users\\samky\\Downloads\\ElleHacks2020\\data\\whitelisted_domains.txt", "r");
    FILE *whitelisted_urls = fopen("C:\\Users\\samky\\Downloads\\ElleHacks2020\\data\\whitelisted_urls.txt", "r");

    char input[MAX_STR_LEN] = "@ontarie.ca"; //should not be flagged

    type = check_type_input(input);

    if (type == 1){
        if (return_bool(input, whitelisted_domains)){
            FILE *suspect_domains = fopen("C:\\Users\\samky\\Downloads\\ElleHacks2020\\data\\suspect_domains.txt", "a");
            if(suspect_domains == NULL){  
                exit(1);             
            }
            fprintf(suspect_domains,"%s",input);
            fclose(suspect_domains);

        }
    }else{
        if (return_bool(input, whitelisted_urls)){
            FILE *suspect_urls = fopen("C:\\Users\\samky\\Downloads\\ElleHacks2020\\data\\suspect_urls.txt", "a");
            if(suspect_urls == NULL){  
                exit(1);             
            }
            fprintf(suspect_urls,"%s",input);
            fclose(suspect_urls);
        }
    }
    fclose(whitelisted_domains);
    fclose(whitelisted_urls);
    return 0;
}