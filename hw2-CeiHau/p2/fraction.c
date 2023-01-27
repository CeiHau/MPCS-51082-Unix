#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// https://en.wikipedia.org/wiki/Euclidean_algorithm
int gcd(int m, int n){
   if(m==0){
    return n;
   }
   return gcd(n, m%n);
}

int reduce(int x, int y) {
    int cd = gcd(x, y);
    printf("%d/%d\n", x/cd, y/cd);
    return 1;
}

int main(){

    char line[256];

    while(fgets(line, 256, stdin)) {
        int x  = atoi(strtok(line, "/"));
        int y = atoi(strtok(NULL, "/"));
        reduce(x,y);       
    }
}