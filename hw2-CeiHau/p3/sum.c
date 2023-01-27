#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int getDigit(int digit, int pos) {
    int remain;
    while(digit !=0 && pos !=0){
        remain = digit % 10;
        digit /= 10;
        pos--;
    }
    if(pos !=0){
        return -1;
    }else {
        return remain;
    }
}

int main(){
    int i = 1;
    int digit;
    printf("Enter in integer: ");
    scanf("%d", &digit);

    int sum = 0;
    int temp = getDigit(digit, i++);
    while((temp) != -1){
        sum += temp;
        temp = getDigit(digit, i++);
    }
    printf("%d", sum);
  
}