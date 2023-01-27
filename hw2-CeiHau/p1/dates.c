#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int transfer(char * date, int *day, int *month, int *year){
    if(strlen(date) != 8 || date[2] != '/' || date[5] != '/') {
        return 0;
    } else {
        char d[3];
        char m[3];
        char y[3];
        m[0] = date[0],m[1] = date[1],m[2] = '\0';
        d[0] = date[3],d[1] = date[4],d[2] = '\0';
        y[0] = date[6],y[1] = date[7],y[2] = '\0';
        *month = atoi(m);
        *day = atoi(d);
        *year = atoi(y);
    }
    return 1;

}

int main(){
    // char first_date[10];
    // char second_date[10];
    char *first_date = (char*) malloc(sizeof(char) * 10);
    char *second_date = (char*) malloc(sizeof(char) * 10);

    printf("Enter first date(mm/dd/yy):");
    scanf("%s", first_date);

    printf("Enter second date(mm/dd/yy):");
    scanf("%s", second_date);

    int fday, fmonth, fyear;
    int sday, smonth, syear;
    if(transfer(first_date, &fday, &fmonth, &fyear) && transfer(second_date, &sday, &smonth, &syear)){
        printf("invalid date");
    } else{
        return 0;
    }

    if(fyear*10000 + fmonth * 100 + fday < syear * 10000 + smonth* 100 + sday){
        printf("%s comes before %s",first_date, second_date );
    }else if(fyear*10000 + fmonth * 100 + fday > syear * 10000 + smonth* 100 + sday){
        printf("%s comes before %s",second_date, first_date );
    } else{
        printf("%s is the same as %s",first_date, second_date );
    }

}