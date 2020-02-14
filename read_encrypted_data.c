#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX_STRING_LENGTH 2048

long long long_array[MAX_STRING_LENGTH];
char input[MAX_STRING_LENGTH];

/* improvements:
KEEP AS INT AT INTERMEDIATE STEPS TO SAVE ON MEMORY

TAKE INPUT FROM DATABASE : NEED A SEARCH FUNCTION IN DATABASE TO FIND REQUIRED DATA PIECE TO UNENCRYPT

*/
void switch_second_indices(long long long_array[MAX_STRING_LENGTH]){
    //if odd number of indices, leave last character alone

    for (int i = 0; long_array[i + 1] != (long long)-1; i = i + 2){
        long long first = long_array[i];
        long_array[i] = long_array[i +1];
        long_array[i+1] = first;
    }
}

void reverse(long long *long_array){
    //switch value stored at each index from outside in
    int length = 0;
    for (length; long_array[length] != (long long)-1; length++);

    long long temp;
    for (int i = 0; i < length/2; i ++){
        temp = *(long_array + i);
        *(long_array + i) = *(long_array + (length - i - 1));
        *(long_array + (length - i -1)) = temp;
    }
}

long long binary_to_decimal(long long binary_input){
    long long decimal_output = 0;
    int i = 0;
    int remainder;

    while (binary_input > 0){
        remainder = binary_input % 10;
        binary_input = binary_input/10;
        decimal_output += remainder * pow(2,i);
        i++;
    } return decimal_output;
}

void ascii_to_char(long long long_array[MAX_STRING_LENGTH]){
    int i = 0;
    for (i; long_array[i] != (long long)-1; i++){
        input[i] = long_array[i];
    }
    input[i - 1] = '\0';
}
//assume input is given as a string of chars
char input[MAX_STRING_LENGTH];
long long long_array[MAX_STRING_LENGTH];

int main(){
    long long sample_long_array[MAX_STRING_LENGTH] = {(long long)1100101,
                  (long long)1101111, //J
                  (long long)1101101, //o
                  (long long)101110, //h
                  (long long)1100011, //n
                  (long long)1101001, //@
                  (long long)1101100, //e
                  (long long)1101101, //m
                  (long long)1100001, //a
                  (long long)1000000, //i
                  (long long)1100101, //l
                  (long long)1101000, //.
                  (long long)1101110, //c
                  (long long)1001010, //o
                  (long long)1101111, //m
                  (long long)-1};

    int length = 0;
    for (length; sample_long_array[length] != (long long)-1; length++);
    sample_long_array[length] = (long long)-1;

    reverse(sample_long_array);
    switch_second_indices(sample_long_array);

    for (int i = 0; sample_long_array[i] != (long long)-1; i++){
        sample_long_array[i] = binary_to_decimal(sample_long_array[i]);
    }

    ascii_to_char(sample_long_array);

    printf("%s \n", input); //would be an export once interaction with cloud complete

    return 0;    
}