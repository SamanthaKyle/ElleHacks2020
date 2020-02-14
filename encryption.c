#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

//TEST FURTHER EDGE CASES: SURVEY GROUP

#define MAX_STRING_LENGTH 2048
//assume input is given as a string of chars
char input[MAX_STRING_LENGTH];
long long long_array[MAX_STRING_LENGTH];

void convert_to_ascii (char input[MAX_STRING_LENGTH]){
    int length = strlen(input);
    for (int idx = 0; idx < length; idx ++){
        *(long_array + idx) = (long long)*(input + idx);
    }long_array[length + 1] = (long long)-1;
}

long long convert_decimal_to_binary(int decimal_form) {
    long long binary_result;
    binary_result = 0;
    int remainder, i = 1, step = 1;

    while (decimal_form != 0) {
        remainder = decimal_form % 2;
        decimal_form /= 2;
        binary_result += remainder * i;
        i *= 10;
    }

    return binary_result;
}

void ascii_to_bin(long long long_array[MAX_STRING_LENGTH]){

    for (int i = 0; long_array[i] != (long long)-1; i++){
        *(long_array + i) = convert_decimal_to_binary(*(long_array + i));
    }
}

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

int main(){
    strcpy(input, "John@email.com");
    convert_to_ascii(input);
    switch_second_indices(long_array); 
    reverse(long_array);
    ascii_to_bin(long_array);

    for (int i = 1; long_array[i] != (long long) - 1; i++){ 
        printf("%d \n", long_array[i]);//print left in for dispaly, when interactivity with cloud database established, this would instead be an export
    }

    return 0;
}